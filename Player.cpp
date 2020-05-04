#include "include\Player.h"

// === public === //
void Player::create() 
{
	type = TYPE_PLAYER;
	hitBoxSize = Vector2f(20, 40);
	anim.create(TEX_OBJECTS, (Frame*)framesObjects);
    anim.set(0, 0, 0);
}

void Player::update() 
{
    movement();
    gameplay();
    animation();
    anim.tick();
}

void Player::draw(Camera& cam) 
{
    // Animation angle
    if (animAngle == 360)
        animAngle = 0;


    if (invicTimer == 0 || (invicTimer > 0 && invicTimer % 8 >= 4) || action == ACT_HURT)
        anim.draw(cam, pos, animFlip, false, anim8Angle);
}

void Player::moveCam(Camera& cam)
{
    if (action == ACT_DIE)
        return;

    if (camLagTimer > 0) {
        camLagTimer--; 
        return;
    }

	float _x = pos.x - SCREEN_WIDTH / 2;
	float _y = (pos.y - shiftY) - SCREEN_HEIGHT / 2;

	Vector2f camPos = cam.getPos();

	int _leftBorder = camPos.x - 16;
	int _rightBorder = camPos.x;
	int _topBorder = camPos.y - 32;
	int _bottomBorder = camPos.y + 32;

	if (_x < _leftBorder)
		camPos.x -= fmin(_leftBorder - _x, 16.0);
	else if (_x > _rightBorder)
		camPos.x += fmin(_x - _rightBorder, 16.0);

	if (ground) {
		if (ysp > 6.0)
			camPos.y += fmin(fmax(_y - camPos.y, -16.0), 16.0);
		else
			camPos.y += fmin(fmax(_y - camPos.y, -6.0), 6.0);
	}
	else {
		if (_y < _topBorder)
			camPos.y -= fmin(_topBorder - _y, 16.0);
		else if (_y > _bottomBorder)
			camPos.y += fmin(_y - _bottomBorder, 16.0);
	}

	//cam.setPos(camPos);
    cam.setPos(Vector2f(int(camPos.x), int(camPos.y)));
}

Vector2i Player::getRotatedPoint(Vector2f _center, int rW, int rH, float angle)
{
    return Vector2i(int(_center.x + (cosf(radians(angle)) * rW) + (sinf(radians(angle)) * rH)), 
                    int(_center.y + (cosf(radians(angle)) * rH) - (sinf(radians(angle)) * rW)));

}

Tile Player::getGround(Vector2i& _senPos, int rW, int rH, float _ang) 
{
    Tile tile = (*trn).getTile(_senPos);

    if (tile.getHeight(_senPos, flrMode * 90) != 0) {
            if (tile.getHeight(_senPos, flrMode * 90) >= 16) {
                _senPos = getRotatedPoint(pos, rW, rH - 16, flrMode * 90);
                tile = (*trn).getTile(_senPos);
                if (tile.getHeight(_senPos, flrMode * 90) == 0) {
                    _senPos = getRotatedPoint(pos, rW, rH, flrMode * 90);
                    tile = (*trn).getTile(_senPos);
                }
            }
        } 

    if (tile.getHeight(_senPos, flrMode * 90) == 0) {
        _senPos = getRotatedPoint(pos, rW, rH + 16, flrMode * 90);
        tile = (*trn).getTile(_senPos);
    }

    return tile;
}

void Player::terrainCollision(Camera& cam) 
{

    if (action == ACT_DIE) {
        ground = false;
        flrMode = FLOOR;
		angle = 0.0;
		if (ysp < 16.0)
			    ysp += PL_GRAV;
        return;
    }

    float senAngle = flrMode * 90;
    // ==== Layering ==== //
    (*trn).setLayer(layer);

    // ===== Celling Collision ==== //
	#pragma region Celling Collision 

    Vector2i sensorC = Vector2i(pos.x - gndWidth, pos.y - gndHeight);
    Vector2i sensorD = Vector2i(pos.x + gndWidth, pos.y - gndHeight); 

    Tile tileC = (*trn).getTile(sensorC);
    Tile tileD = (*trn).getTile(sensorD);

    int heightTileC = tileC.getHeight(sensorC, 180);
    int heightTileD = tileD.getHeight(sensorD, 180);

	if (!ground && ysp < 0) {
            
        if (heightTileC != 0 || heightTileD != 0) {
            int mainHeight = 0;

            if      (heightTileC == 0) mainHeight = tileD.pos.y + heightTileD;
            else if (heightTileD == 0) mainHeight = tileC.pos.y + heightTileC;
            else    mainHeight = max(tileC.pos.y + heightTileC, tileD.pos.y + heightTileD); 
                
            if (pos.y - gndHeight <= mainHeight) 
            {
                if (heightTileC > heightTileD) 
                    angle = tileC.angle;
                else 
                    angle = tileD.angle;

                if ((angle > 90.0 && angle <= 135) || (angle >= 225 && angle < 270)) {
                    action = ACT_NORMAL;
                    gndHeight = 20;
                    pos.y = mainHeight + gndHeight;
                    gsp = ysp * -fsign(sinf(radians(angle)));
                    ysp = 0;
                    ground = true;
                    flrMode = FlrMode::BOTTOM;
                    senAngle = flrMode * 90;
                } else {
                    ysp = 0;
                    angle = 0;
                    flrMode = FlrMode::FLOOR;
                    pos.y = mainHeight + gndHeight;
                }
            }
        }
    }
    
	#pragma endregion
    
    // ===== Wall collision ====== //

	#pragma region Wall Collision

    Vector2i sensorE = getRotatedPoint(pos, -10,  0, senAngle);
    Vector2i sensorF = getRotatedPoint(pos,  10,  0, senAngle);

    Tile tileE = (*trn).getTile(sensorE);
    Tile tileF = (*trn).getTile(sensorF);

    int heightE = tileE.getHeight(sensorE, int(senAngle+270) % 360);
    int heightF = tileF.getHeight(sensorF, int(senAngle+90) % 360);

    if (ground) {
        if (gsp > 0)
            heightE = 0;
        if (gsp < 0)
            heightF = 0;
    } 

    if (angle > 90.0 && angle < 270.0) {
        heightE = 0;
        heightF = 0;
    }

    if (xsp > abs(ysp))
        heightE = 0;
    if (-xsp > abs(ysp))
        heightF = 0;


    switch(flrMode) 
    {
        case FlrMode::FLOOR:
            if (heightE != 0 && pos.x - 10 < tileE.pos.x + heightE) {
                pos.x = tileE.pos.x + heightE + 10;
                xsp = 0; // For air mode
                gsp = 0;
            }
            if (heightF != 0 && (pos.x + 10 > (tileF.pos.x + 16 - heightF))) {
                pos.x = tileF.pos.x + 16 - heightF - 10;
                xsp = 0; // For air mode
                gsp = 0;
            }
            break;
        case FlrMode::BOTTOM:
            if (heightE != 0 && pos.x + 10 > tileE.pos.x + 16 - heightE) {
                pos.x = tileE.pos.x + 16 - heightE - 10;
                gsp = 0;
            }
            if (heightF != 0 && (pos.x - 10 < (tileF.pos.x + heightF))) {
                pos.x = tileF.pos.x + heightF + 10;
                gsp = 0;
            }
            break;
        case FlrMode::RIGHT_WALL:
            if (heightE != 0 && pos.y + 10 > tileE.pos.y + 16 - heightE) {
                pos.y = tileE.pos.y + 16 - heightE - 10;
                gsp = 0;
            }
            if (heightF != 0 && (pos.y - 10 < (tileF.pos.y + heightF))) {
                pos.y = tileF.pos.y + heightF + 10;
                gsp = 0;
            }
            break;
        case FlrMode::LEFT_WALL:
            if (heightE != 0 && pos.y - 10 < tileE.pos.y + heightE) {
                pos.y = tileE.pos.y + heightE + 10;
                gsp = 0;
            }
            if (heightF != 0 && (pos.y + 10 > (tileF.pos.y + 16 - heightF))) {
                pos.y = tileF.pos.y + 16 - heightF - 10;
                gsp = 0;
            }
            break;
    }
	#pragma endregion
    
    // ====== Ground Collision ====== //
	#pragma region Ground Collision


    bool isFalling = true;

    Vector2i sensorA = getRotatedPoint(pos, -gndWidth, gndHeight, senAngle);
    Vector2i sensorB = getRotatedPoint(pos, gndWidth,  gndHeight, senAngle);

    Tile tileA = getGround(sensorA, -gndWidth, gndHeight, senAngle);  // Left Sensor
    Tile tileB = getGround(sensorB,  gndWidth, gndHeight, senAngle);  // Right Sensor

    int heightTileA = tileA.getHeight(sensorA, senAngle);
    int heightTileB = tileB.getHeight(sensorB, senAngle);

    /*cam.drawRect(TEX_SONIC, IntRect(4,4, 16, 16), Vector2f(int(tileA.pos.x), int(tileA.pos.y)), 
                 Vector2i(0,0), false, false, 0);        
    cam.drawRect(TEX_SONIC, IntRect(4,4, 16, 16), Vector2f(int(tileB.pos.x), int(tileB.pos.y)), 
                 Vector2i(0,0), false, false, 0);   

    cam.drawLine(Vector2f(pos.x, pos.y), Vector2f(sensorA.x, sensorA.y)); 
    cam.drawLine(Vector2f(pos.x, pos.y), Vector2f(sensorB.x, sensorB.y)); */

            
    if (!standOnObj && ((heightTileA != 0 || heightTileB != 0) && ((ground) || 
        (!ground && ysp >= 0.0 && flrMode == FlrMode::FLOOR && 
        ((pos.y + PL_FOOT_LEVEL > (min(tileA.pos.y + 16 - heightTileA, tileB.pos.y + 16 - heightTileB)))
        ))))) {

        int tileShift = 16;
        if (flrMode == FlrMode::BOTTOM || flrMode == FlrMode::LEFT_WALL)
            tileShift = 0;

        int aHeight, bHeight;
        if (flrMode == FlrMode::FLOOR || flrMode == FlrMode::BOTTOM) {
            aHeight = tileA.pos.y + tileShift - cosf(radians(senAngle)) * (heightTileA + gndHeight);
            bHeight = tileB.pos.y + tileShift - cosf(radians(senAngle)) * (heightTileB + gndHeight);
        } else {
            aHeight = tileA.pos.x + tileShift - sinf(radians(senAngle)) * (heightTileA + gndHeight);
            bHeight = tileB.pos.x + tileShift - sinf(radians(senAngle)) * (heightTileB + gndHeight);
        }

        float* posPtr;
        if (flrMode == FlrMode::LEFT_WALL || flrMode == FlrMode::RIGHT_WALL)
            posPtr = &pos.x;
        else 
            posPtr = &pos.y;

        if (heightTileB == 0) {
            angle = tileA.angle;
            *posPtr = aHeight;
        } else if (heightTileA == 0) {
            angle = tileB.angle;
            *posPtr = bHeight;
        } else {
            if (flrMode == FlrMode::FLOOR || flrMode == FlrMode::RIGHT_WALL)
                *posPtr = min(aHeight, bHeight);
            else if (flrMode == FlrMode::BOTTOM || flrMode == FlrMode::LEFT_WALL)
                *posPtr = max(aHeight, bHeight);

            if (*posPtr == bHeight)      angle = tileB.angle;
            else if (*posPtr == aHeight) angle = tileA.angle;
        }
            
        // Set angle
        if (angle == 0.0 || angle == 360.0)
            angle = 90.0 * float(flrMode);
     
        // Landing
        if (!ground) {
            if (((angle >= 0.0) && (angle < 22.5)) || ((angle > 337.5) && (angle <= 360.0))) {
                gsp = xsp;
            } else if (((angle >= 22.5) && (angle < 45.0)) || ((angle > 315.0) && (angle <= 337.5))) {
                if (abs(xsp) > ysp)
                    gsp = xsp;
                else
                    gsp = ysp * 0.5 * -fsign(sinf(radians(angle)));
            } else if (((angle >= 45.0) && (angle < 90.0)) || ((angle > 270.0) && (angle <= 315.0))) {
                if (abs(xsp) > ysp)
                    gsp = xsp;
                else
                    gsp = ysp * -fsign(sinf(radians(angle)));
            }

			// set normal state if we rolling in air
			if (action == ACT_ROLL)
				action = ACT_NORMAL;
                
        }

        isFalling = false;
    }
	#pragma endregion

    // ===== Gravity ===== //
    if (isFalling && !standOnObj) {
        ground = false;
        flrMode = FLOOR;
		angle = 0.0;

        // Air drug
        if (!ground && ysp < 0.0 && ysp > -4.0)
            xsp -= (int(xsp) / 0.125) / 256;

		if (ysp < 16.0) {
            if (action != ACT_HURT)
			    ysp += PL_GRAV;
            else 
                ysp += 0.1875;
        }
    } else {
        ground = true;   
    }

    // === Fall if doesnt have enough speed ===
    if (ground && (fabs(gsp) < 2.5) && (flrMode != FlrMode::FLOOR)) {
        if (angle >= 90.0 && angle <= 270.0) {
            flrMode = FlrMode::FLOOR;
            ground = false;
            angle = 0;
            isFalling = true;
            gsp = 0.0;
        }
        horizontalLockTimer = 30;
    }

    switchFlrModes();

    // Return to normal state after landing
    if (ground && (action == ACT_JUMP || action == ACT_SPRING))
        action = ACT_NORMAL;

}

void Player::entitiesCollision(std::list<Entity*>& entities, Camera& cam)
{
    if (action == ACT_DIE)
        return;

	std::list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); it++) {
        if (!(*it)->isInCamera(cam)) continue;
        // Collsion Sign Post
		if ((*it)->getType() == TYPE_SIGN_POST) {
			if (pos.x >= (*it)->getPos().x) {
                SignPost* sp = (SignPost*)*it;
                sp->setAnim(true);
                cam.setRightBorder((*it)->getPos().x + SCREEN_WIDTH / 2);
                canHorMove = false;
                if (action == ACT_SKID)
                    action = ACT_NORMAL;
                if (!ground)
                    xsp += PL_AIR;
                else
                    gsp += PL_ACC;
                endLv = true;
            }

		}
		// Collsion Spring
		if ((*it)->getType() == TYPE_SPRING) {
			Spring* spring = (Spring*)*it;
			if (collisionBottom(*spring)) {
				pos.y = spring->getPos().y - spring->getHitBoxSize().y / 2 - hitBoxSize.y / 2 - shiftY;
				action = ACT_SPRING;
				ground = false;
				if (spring->isRed())
					ysp = -16.0;
				else
					ysp = -10.0;
				spring->doAnim();
			}
		}
		// Collision Ring
		if ((*it)->getType() == TYPE_RING) {
			Ring* ring = (Ring*)*it;
			if (collisionMain(*ring) && ringTimer == 0) {
				ring->destroy();
                AnimMgr rSfx;
                rSfx.create(TEX_OBJECTS, (Frame*)framesObjects);
                rSfx.set(84, 87, 0.5);
                rings++;
                entities.push_back(new Sfx(Vector2f(ring->getPos().x, ring->getPos().y), rSfx));
			}
		}
        // Collision Enemy
		if ((*it)->getType() == TYPE_ENEMY) {
			Enemy* en = (Enemy*)*it;
			if (collisionMain(*en)) {
				if (action == ACT_JUMP || action == ACT_ROLL || action == ACT_SPINDASH) {
                    if (!ground) {
                        if (ysp > 0) {
                            ysp *= -1;
                        } else {
                            ysp -= sign(ysp);
                        }
                    } 
                    en->destroy();

                    AnimMgr rSfx;
                    rSfx.create(TEX_OBJECTS, (Frame*)framesObjects);
                    rSfx.set(95, 99, 0.125);
                    entities.push_back(new Sfx(Vector2f(en->getPos().x, en->getPos().y), rSfx));
                } else {
                    getHit(entities);
                }
			}
		}
        //Bullet
        if ((*it)->getType() == TYPE_BULLET) {
			if (collisionMain(**it)) 
                getHit(entities);
		}
        // Collision Layer Switch
		if ((*it)->getType() == TYPE_LAYER_SWITCH) {
			LayerSwitcher* ls = (LayerSwitcher*)*it;
			if (collisionMain(*ls)) {
				if (ls->getMode() == 0 && xsp > 0) {
                    layer = 0;
                } else if (ls->getMode() == 1 && xsp < 0) {
                    layer = 1;
                } else if (ls->getMode() == 2 && xsp > 0) {
                    layer = 0;
                } else if (ls->getMode() == 2 && xsp < 0) {
                    layer = 1;
                }
			}
		}
        //STube
        if ((*it)->getType() == TYPE_STUBE_CNTRL) {
			GimGHZ_STube* _stube = (GimGHZ_STube*)*it;
			if (collisionMain(*_stube)) {
				if (_stube->getMode() == 0) {
                    if (gsp >= 0 || xsp >= 0) 
                        sTube = true;
                    else if (gsp < 0 && xsp < 0)
                        sTube = false;
                } else {
                    if (gsp >= 0 || xsp >= 0) 
                        sTube = false;
                    else if (gsp < 0 && xsp < 0)
                        sTube = true;
                }
			}
		}
        // GHZ Bridge
        if ((*it)->getType() == TYPE_BRIDGE) {
			GimGHZ_Bridge* br = (GimGHZ_Bridge*)*it;
            if ((!ground && collisionBottom(**it)) || (ground && collisionBottomPlatform(**it, 14))) {
                br->setActive(true);
                pos.y = ((*br).getY()) - ((*br).getHitBoxSize().y / 2) - (hitBoxSize.y / 2);
                ground = true;
            }
        }
        // GHZ Slope Platform
        if ((*it)->getType() == TYPE_GHZ_SLP_PLATFORM) {
			GimGHZ_SlpPlatform* slope = (GimGHZ_SlpPlatform*)*it;
            if (((collisionBottom(*slope, 12) && ground) ||
                 (collisionBottom(*slope, 1)  && !ground)) && ysp >= 0 &&
                 pos.y < slope->getPos().y - 30) {
                    int _x = pos.x - (slope->getPos().x - (slope->getHitBoxSize().x / 2));
                    pos.y = slope->getPos().y - (slope->getHeight(_x)) - 22 - hitBoxSize.y / 2;
                    if (!standOnObj) {
                        standOnObj = true;
                        standOnID = it;
                        ground = true;
                        gsp = xsp;
                    }
            }
        }
        // Collision Solid
        if ((*it)->isSolid()) {
			if (collisionRight(**it) && xsp > 0.0) {
                pos.x = (*it)->getPos().x - (*it)->getHitBoxSize().x / 2 - hitBoxSize.x / 2;
                xsp = 0.0;
                gsp = 0.0;
            } 
            if (collisionLeft(**it) && xsp < 0.0) {
                pos.x = (*it)->getPos().x + (*it)->getHitBoxSize().x / 2 + hitBoxSize.x / 2;
                xsp = 0.0;
                gsp = 0.0;
            } 

            if (collisionTop(**it) && ysp < 0.0) {
				pos.y = (*it)->getPos().y + (*it)->getHitBoxSize().y / 2 + hitBoxSize.y / 2;
				ysp = 0.0;
				gsp = 0.0;
			}
        }
        // Platform
        if ((*it)->isPlatform()) {
			if (((collisionBottomPlatform(**it, 12) && ground && ysp >= 0) ||
                 (collisionBottomPlatform(**it, 1)  && !ground)) && ysp >= 0) {
                if ((*it)->isPlatPushUp())
                    pos.y = (*it)->getPos().y - (*it)->getHitBoxSize().y / 2 - hitBoxSize.y / 2;
                    
                if (!standOnObj) {
                    standOnObj = true;
                    standOnID = it;
                    ground = true;
                    gsp = xsp;
                }

                if ((*it)->getType() == TYPE_PLATFORM) {
                    GimGHZ_Platform* _pltfrm = (GimGHZ_Platform*)*it;
                    if (_pltfrm->getDir() < 2)
                        pos.x += _pltfrm->getSpd();
                }
			} 
        }
	}

    if (standOnObj) {
        if (!collisionBottomPlatform(**standOnID, 12) || ysp < 0) {
            standOnObj = false;
        }
    }
}
// === private === //
void Player::movement() {
    if (pos.x - 9 < 0 && xsp < 0) {pos.x = 9; gsp = 0; xsp = 0;}

    if (ground) {
		if ((flrMode == FlrMode::FLOOR && gsp != 0) || (flrMode != FlrMode::FLOOR)) {
			if (action != ACT_ROLL) {
				gsp -= PL_SLP * sinf(radians(angle));
			} else {
				if (sign(gsp) == sign(sinf(radians(angle))))
					gsp -= PL_SLP_ROLL_UP * sinf(radians(angle));
				else
					gsp -= PL_SLP_ROLL_DOWN * sinf(radians(angle));
			}
		}
        xsp = gsp * cosf(radians(angle));
        ysp = gsp * -sinf(radians(angle)); 
    }

    pos.x += xsp;
    pos.y += ysp;

    if (ground) {
        if (action == ACT_NORMAL || action == ACT_SKID) {
            if (Keyboard::isKeyPressedRight() && !Keyboard::isKeyPressedLeft() && canHorMove) {
                if (gsp < 0.0)
                    gsp += PL_DEC;
                else if (gsp < PL_TOP)
                    gsp += PL_ACC;
            } else if (Keyboard::isKeyPressedLeft() && !Keyboard::isKeyPressedRight() && canHorMove) {
                if (gsp > 0.0)
                    gsp -= PL_DEC;
                else if (gsp > -PL_TOP)
                    gsp -= PL_ACC;
            } else {
                gsp -= fmin(fabs(gsp), PL_FRC) * float(fsign(gsp));
            }
        } else if (action == ACT_ROLL) {
            if (Keyboard::isKeyPressedRight() && !Keyboard::isKeyPressedLeft() && canHorMove) {
                if (gsp < 0.0)
                    gsp += PL_DEC_ROLL;
            } else if (Keyboard::isKeyPressedLeft() && !Keyboard::isKeyPressedRight() && canHorMove) {
                if (gsp > 0.0)
                    gsp -= PL_DEC_ROLL;
            }
            gsp -= fmin(fabs(gsp), PL_FRC_ROLL) * float(fsign(gsp));
        }
    } else {
        if ((Keyboard::isKeyPressedRight()) && (xsp < PL_TOP) && canHorMove)
            xsp += PL_AIR;
        else if ((Keyboard::isKeyPressedLeft()) && (xsp > -PL_TOP) && canHorMove)
            xsp -= PL_AIR;

    }
}

void Player::gameplay() {

    // Invicibility Timer
    if (invicTimer > 0 && action != ACT_HURT)
        invicTimer--;
    if (ringTimer > 0)
        ringTimer--;

    // Hor lock timer
    if (horizontalLockTimer > -1) {
        if (horizontalLockTimer == 0)
            canHorMove = true;
        else
            canHorMove = false;

        horizontalLockTimer--;
    }

    // S Tube
    if (sTube) {
        action = ACT_ROLL;
        if (gsp == 0.0) {
            if (!animFlip)
                gsp = 2.0;
            else 
                gsp = -2.0;
        }
    }

    // Skid
    if (action == ACT_NORMAL && fabs(gsp) > 2.5 && ground && flrMode == 0) {
        if (gsp > 0 && Keyboard::isKeyPressedLeft() ||
            gsp < 0 && Keyboard::isKeyPressedRight())
                action = ACT_SKID;
    } 
    if (action == ACT_SKID) {
        if (gsp <= 0 && Keyboard::isKeyPressedLeft())
            action = ACT_NORMAL;
        else if (gsp >= 0 && Keyboard::isKeyPressedRight())
            action = ACT_NORMAL;

        if (gsp == 0 || flrMode != 0)
            action = ACT_NORMAL;
    }

    // Spindash timer
    if (spindashTimer > 0)
        spindashTimer--;

    // === Jump ===
    if (Keyboard::isKeyPressedAction() && ground && action != ACT_HURT && !sTube) {
        ground = false;
        standOnObj = false;
        action = ACT_JUMP;

        xsp -= PL_JMP * sinf(radians(angle));
        ysp -= PL_JMP * cosf(radians(angle)); 
    }

    if ((action == ACT_JUMP) && (ysp < -4.0) && (!Keyboard::isKeyPressedAction()))
        ysp = -4.0;

    // === Spin Dash ===
    if ((action == ACT_NORMAL) && (ground) && (Keyboard::isKeyPressedSpindash())) {
        if (fabs(gsp) <= 1.0) {
            spindashTimer = 45;
            action = ACT_SPINDASH;
            pos.y += 5;
			if (animFlip)
				isSpindashDirRight = false;
			else
				isSpindashDirRight = true;
        } else {
            action = ACT_ROLL;
            pos.y += 5;
        }
    }

    if ((action == ACT_SPINDASH) && (!Keyboard::isKeyPressedSpindash())) {
        if (spindashTimer == 0) {
            action = ACT_ROLL;
            if (isSpindashDirRight) {
                gsp = 12.f;
                animFlip = false;
            } else {
                gsp = -12.f;
                animFlip = true;
            }
            camLagTimer = 16;
        } else {
            action = ACT_NORMAL;
        }
    }

    if ((ground) && ((action == ACT_ROLL) && (gsp == 0.0))) {
        action = ACT_NORMAL;
        pos.y -= 5;
    }

    // Shift y pos and change ground sensor width when player is rolling 
    if (action == ACT_JUMP || action == ACT_SPINDASH || action == ACT_ROLL) {
		hitBoxSize = Vector2f(20, 30);
        shiftY = 5;
        gndWidth = 7;
        gndHeight = 15;
    } else {
		hitBoxSize = Vector2f(20, 40);
        shiftY = 0;
        gndWidth = 9;
        gndHeight = 20;
    }

    // Hurt
    if (action == ACT_HURT) {
        canHorMove = false;
        if (ground) {
            canHorMove = true;
            action = ACT_NORMAL;
            xsp = 0;
        }
    }
}

void Player::animation() {
    //Animation angle
    if (ground) {
		if ((action != ACT_ROLL) && (action != ACT_SPINDASH) && (action != ACT_SKID)  && (abs(gsp) > 0))
            animAngle = angle;
		else
			animAngle = 0.0;
	} else {
        if (animAngle != 0 && action != ACT_JUMP) {
			if (animAngle > 180.0)
				animAngle += 4.0;
			else
				animAngle -= 4.0;

			if (animAngle > 360.0)
				animAngle = 0.0;
			else if (animAngle < 0.0)
				animAngle = 0.0;
        } else {
            animAngle = 0;
        }
    }

    //Transform Angle
    diaAnim = false;
    if (animAngle > 337.5 || animAngle <= 22.5) {
        anim8Angle = 0;
    } else if (animAngle > 22.5 && animAngle <= 67.5) {
        if (!animFlip) anim8Angle = 0;
        else anim8Angle = 270;
        diaAnim = true;
    } else if (animAngle > 67.5 && animAngle <= 112.5) {
        anim8Angle = 270;
    } else if (animAngle > 112.5 && animAngle <= 157.5) {
        if (!animFlip) anim8Angle = 270;
        else anim8Angle = 180;
        diaAnim = true;
    } else if (animAngle > 157.5 && animAngle <= 202.5) {
        anim8Angle = 180;
    } else if (animAngle > 202.5 && animAngle <= 247.5) {
        if (!animFlip) anim8Angle = 180;
        else anim8Angle = 90;
        diaAnim = true;
    } else if (animAngle > 247.5 && animAngle <= 292.5) {
        anim8Angle = 90;
    } else if (animAngle > 292.5 && animAngle <= 337.5) {
        if (!animFlip) anim8Angle = 90;
        else anim8Angle = 0;
        diaAnim = true;
    } 

    // Set sprite direction
    if (ground && action != ACT_ROLL) {
        if ((gsp < 0.0) && (Keyboard::isKeyPressedLeft()))
            animFlip = true;
        else if ((gsp > 0.0) && (Keyboard::isKeyPressedRight()))
            animFlip = false;
    } else {
        if (Keyboard::isKeyPressedLeft())
            animFlip = true;
        else if (Keyboard::isKeyPressedRight())
            animFlip = false;
    }

    // Set animations from actions
    if (!ground || gsp != 0.0)
        animIdleTimer = 288;
    if (action == ACT_NORMAL) {
        if (ground) {
            if (fabs(gsp) == 0.0) {
                if (animIdleTimer > 0) {
                    anim.set(0, 0, 0);
                    animIdleTimer--;
                } else  {
                    animIdleTimer--;
                    if (animIdleTimer < -72)
                        anim.set(2, 3, 0.042);
                    else 
                        anim.set(1, 1, 0);
                }
            } 
        }
        if ((fabs(gsp) > 0.0) && (fabs(gsp) < 6.0)) {
            if (diaAnim) 
                anim.set(26, 31, 1.0 / int(fmax(3, 8.0-abs(gsp))) );
            else 
                anim.set(4, 9, 1.0 / int(fmax(3, 8.0-abs(gsp))) );
        } else if ((fabs(gsp) >= 6.0) && (fabs(gsp) < 12.0)) {
            if (diaAnim) 
                anim.set(32, 35, 1.0 / int(fmax(2, 8.0-abs(gsp))) );
             else
                anim.set(11, 14, 1.0 / int(fmax(2, 10.0-abs(gsp))) );
        } else if (fabs(gsp) >= 12.0) {
            if (diaAnim)
                anim.set(47, 50, 1.0 / int(fmax(2, 8.0-abs(gsp))) );
            else 
                anim.set(43, 46, 1.0 / int(fmax(2, 10.0-abs(gsp))));
        }
    } else {
        switch(action) {
            case ACT_JUMP:
                anim.set(15, 22, 1.0 / int(fmax(1, 4.0-abs(gsp))));
                break;
            case ACT_SPINDASH:
                anim.set(15, 22, (float(45 - spindashTimer) / 30));
                break;
            case ACT_ROLL:
                anim.set(15, 22, 1.0 / int(fmax(1, 4.0-abs(gsp))));
                break;
            case ACT_HURT:
                anim.set(36, 36, 0);
                break;
            case ACT_SKID:
                if (int(anim.getCurFrame()) == 25) {
                    anim.set(25, 25, 0);
                } else {
                    anim.set(23, 25, 0.125);
                }
                break;
            case ACT_DIE:
                anim.set(37, 37, 0);
                break;
			case ACT_SPRING:
				if (ysp < 0.0)
					anim.set(51, 53, (0.125 + fabs(ysp) / 25), true);
				else
					anim.set(54, 55, 0.25, false);
				break;
        }
    }
    
}

void Player::switchFlrModes() {
    FlrMode _flrMode = FlrMode(int(roundf(angle / 90.0)) % 4);
    if (flrMode != _flrMode) {
        Vector2i aSensor = getRotatedPoint(pos, -gndWidth, gndHeight, _flrMode * 90);
        Vector2i bSensor = getRotatedPoint(pos, gndWidth,  gndHeight, _flrMode * 90);

        float _angle = 0;

        Tile aTile = (*trn).getTile(aSensor);
        Tile bTile = (*trn).getTile(bSensor);

        if (aTile.getHeight(aSensor, _flrMode * 90) != 0 || bTile.getHeight(bSensor, _flrMode * 90) != 0) {
            if (aTile.getHeight(aSensor, _flrMode * 90) > bTile.getHeight(bSensor, _flrMode * 90)) 
                _angle = aTile.angle;
            else 
                _angle = bTile.angle;

            FlrMode _newFlrMode = FlrMode(int(roundf(_angle / 90.0)) % 4);

            if (_newFlrMode == _flrMode)
                flrMode = _flrMode;
        }
        
    }
}

void Player::getHit(std::list<Entity*>& entities) {
    if (action == ACT_HURT || invicTimer > 0) return;

    if (rings != 0) {
        ringTimer = 64;
        ground = false;
        invicTimer = 120;
        ysp = -4;
        xsp = 2 * -sign(xsp);
        if (xsp == 0) 
            xsp = -2;
        action = ACT_HURT;

        //Rings
        int t = 0;
        float _angle = 101.25f;
        bool _n = false;
        float _spd = 4.0;
        int _h = 1;
        while(t < rings && t < 32) {
            Ring* r = new Ring(pos, *trn, float(cosf(radians(_angle)) * _spd * _h), float(-sinf(radians(_angle)) * _spd));
            r->create();
            entities.push_back(r);
            _h *= -1;
            if (_n)
                _angle += 22.5f;
            _n = !_n;
            t++;
            if (t == 16) {
                _spd = 2;
                _angle = 101.25;
            }
        } 
        rings = 0;
    } else {
        action = ACT_DIE;
        xsp = 0;
        ysp = -7;
        ground = false;
        canHorMove = false;
        endLv = true;
    }
}
