/*
 * object_structure.h
 *
 *  Created on: 18 mar 2026
 *      Author: hasom
 */

#ifndef OBJECT_STRUCTURE_H_
#define OBJECT_STRUCTURE_H_

#define color_black					 0x0000
#define color_red					 0xF800
#define color_green					 0x07E0



typedef struct{
	uint16_t pos_x0;
	uint16_t pos_x1;
	uint16_t pos_y0;
	uint16_t pos_y1;
	int16_t speed;   // potrzbne jak chcemy miec skaknie i opadanie
	uint16_t color;
}object;



void object_draw(object *pObject, uint16_t color);
void player_move(object *pObject);







#endif /* OBJECT_STRUCTURE_H_ */
