/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 13:52:31 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/13 00:39:21 by kain2250         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_STRUCT_H
# define TREE_STRUCT_H
# include <stdint.h>

/*
** Флаги стен - Преграждает путь игрокам и монстрам
*/
# define LD_BLOCK_ALL 0

/*
** Флаги стен - Преграждает путь монстрам
*/
# define LD_BLOCK_MONSTER 0b1

/*
** Флаги стен - Двусторонняя
*/
# define LD_SIDED 0b10

/*
** Флаги стен - Верхняя текстура отключена
*/
# define LD_TOP_TEXTURE 0b100

/*
** Флаги стен - Нижняя текстура отключена
*/
# define LD_BOTOM_TEXTURE 0b1000

/*
** Флаги стен - Секрет
*/
# define LD_SECRET 0b10000

/*
** Флаги стен - Препятствует звуку
*/
# define LD_INTERFERENS_SOUND 0b100000

/*
** Флаги стен - Никогда не показывается на автокарте
*/
# define LD_NEWER_SHOW 0b1000000

/*
** Флаги стен - Всегда показывается на автокарте
*/
# define LD_ALWAYS_SHOW 0b10000000

/*
** Вершина
*/
typedef struct		s_vertex
{
	int16_t			x;
	int16_t			y;
}					t_vertex;
/*
** Стена
*/
typedef struct		s_linedef
{
	uint16_t		start;
	uint16_t		finish;
	uint16_t		flags;
	uint16_t		type;
	uint16_t		mark_sector;
	uint16_t		front;
	uint16_t		rear;
}					t_linedef;
/*
** Сегмент
** start_vert - Номер начальной вершины
** finish_vert - Номер конечной вершины
** angle - угол полного круга от -32768 до 32767
** linedef - Номер стены
** direction - Направление нормали (0 - одинаковое с linedef 1 - противоположно)
** offset - Смещение. Расстояние от linedef до начала сегмента
*/
typedef struct		s_seg
{
	uint16_t		start_vert;
	uint16_t		finish_vert;
	int16_t			angle;
	uint16_t		linedef;
	int16_t			direction;
	uint16_t		offset;
}					t_seg;
/*
** Флаги для спрайтов
** th_skill_level1_2 - сложность 1 и 2 уровня
** th_skill_level3 - сложность 3 уровня
** th_skill_level4_5 - сложность 4 и 5 уровня
** th_mute - враг ждет в засаде
** th_single_nothing - убирает спрайты в одиночной игре
*/
typedef enum		e_thing_flags
{
	th_skill_level1_2 = 0x0001,
	th_skill_level3 = 0x0002,
	th_skill_level4_5 = 0x0004,
	th_mute = 0x0008,
	th_single_nothing = 0x0010
}					t_thing_flags;
/*
** Спрайты
** x - Позиция по x
** y - Позиция по y
** angle - Направление спрайта
** type - Тип спрайта
** flags - флаги t_thing_flags
*/
typedef struct		s_things
{
	int16_t			x;
	int16_t			y;
	int16_t			angle;
	int16_t			type;
	int16_t			flags;
}					t_things;
/*
** Стороны стен
** x - на сколько пикселей сдвинуть все текстуры с
** ** боковым определением по оси X (вправо или влево)
** y - на сколько пикселей сдвинуть все текстуры с
** ** боковым определением по оси Y (вверх или вниз)
** name_of_up - Название верхней текстуры
** name_of_low - Название нижней текстуры
** name_of_mid - Название средней текстуры (основной)
** sector - Номер сектора
*/
typedef struct		s_sidedef
{
	int16_t			x;
	int16_t			y;
	char			name_of_up[9];
	char			name_of_low[9];
	char			name_of_mid[9];
	int16_t			sector;
}					t_sidedef;
/*
** Подсекторы
** count_seg - колличество секторов в подсекторе
** first_seg - номер первого сектора
*/
typedef struct		s_ssectors
{
	uint16_t		count_seg;
	uint16_t		first_seg;
}					t_ssectors;
/*
** Узлы - NODE
*/
typedef struct		s_node
{
	int16_t			x_sliser;
	int16_t			y_sliser;
	int16_t			x_sliser2;
	int16_t			y_sliser2;
	int16_t			right_box[4];
	int16_t			left_box[4];
	int16_t			right_baby;
	int16_t			left_baby;
}					t_node;
/*
** сектор
** hight_flor - высота пола
** hight_cell - высота потолка
** name_tex_flor - название текстуры пола
** name_of_cell - название текстуры потолка
** light - уровень освещенности
** type - тип сектора
** tag - тэг сектора
*/
typedef struct		s_sector
{
	int16_t			hight_flor;
	int16_t			hight_cell;
	char			name_of_flor[9];
	char			name_of_cell[9];
	int16_t			light;
	int16_t			type;
	int16_t			tag;
}					t_sector;
/*
** Дерево
*/
typedef struct		s_tree
{
	void			*data;
	struct s_tree	*node_front;
	struct s_tree	*node_rear;
}					t_tree;
/*
** Пост
** topdelta - Смещение по оси y этого поста в этом патче. Если 0xFF, то конец столбца (недействительный пост)
** length - Длина данных в этом посте
** unused_top - Неиспользуемый байт заполнения; предотвращает ошибку при переполнении столбца из-за потери точности.
** data - Массив пикселей в этом посте, каждый пиксель данных является индексом в палитре PYPALL.
** unused_botom - Неиспользуемый байт заполнения; предотвращает ошибку переполнения столбца из-за потери точности.
*/
typedef struct		s_post
{
	uint8_t			topdelta;
	uint8_t			length;
	uint8_t			unused_top;
	uint8_t			*data;
	uint8_t			unused_botom;
}					t_post;
/*
** Патч
** width - Ширина изображения
** height - Высота изображения
** left_offset - Смещение в пикселях слева от начала координат
** top_offset - Смещение в пикселях ниже начала координат
** columnoffset[] - Массив смещений столбцов относительно заголовка патча
*/
typedef struct		s_patch
{
	uint16_t		width;
	uint16_t		height;
	int16_t			left_offset;
	int16_t			top_offset;
	uint32_t		*columnoffset;
}					t_patch;

typedef struct		s_pnames
{
	uint32_t		num_map_patches;
	char			**name;
}					t_pnames;

typedef struct		s_patches
{
	int16_t			origin_x;
	int16_t			origin_y;
	uint16_t		patch;
	int16_t			stepdir;
	int16_t			colormap;
}					t_patches;

typedef struct		s_map_texture
{
	char			name[9];
	uint32_t		masked;
	int16_t			width;
	int16_t			height;
	uint16_t		patchcount;
	t_patches		*patches;
}					t_map_texture;

typedef struct		s_texture_head
{
	uint32_t		num_texture;
	uint32_t		*offsets;
	t_map_texture	*mtexture;
}					t_texture_head;

#endif
