/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolgin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 20:17:52 by avolgin           #+#    #+#             */
/*   Updated: 2018/09/28 17:21:45 by avolgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include <SDL.h>
# include <SDL_image.h>
# include <libft.h>
# include <fcntl.h>
# include <SDL_ttf.h>
# include <SDL_mixer.h>

# define DOWN SDLK_DOWN
# define UP SDLK_UP
# define LEFT SDLK_LEFT
# define RIGHT SDLK_RIGHT
# define SPACE SDLK_SPACE
# define P SDLK_p
# define MAP holder->map
# define P_X holder->player_x
# define P_Y holder->player_y
# define DIR_X camera->dir_x
# define DIR_Y camera->dir_y
# define PLANE_X camera->plane_x
# define FULLSCREEN SDL_WINDOW_FULLSCREEN
# define OPENGL SDL_WINDOW_OPENGL
# define C_Q (KEYDOWN && holder->event.key.keysym.sym == SDLK_ESCAPE)
# define KEYDOWN holder->event.type == SDL_KEYDOWN
# define ROT_SPEED camera->rot_speed
# define WINDOW holder->window
# define MOV_SP camera->move_speed
# define WHITE (SDL_Color){255, 255, 255, 255}
# define LINE_H (camera->line_height)
# define WIDTH holder->width
# define HEIGHT holder->height
# define POINT ((camera->draw_start << 8) - (HEIGHT << 7) + (LINE_H << 7))
# define START_SCR holder->start->start_screen
# define DELTA_DIST_X camera->delta_dist_x
# define DELTA_DIST_Y camera->delta_dist_y
# define WALL_X_FL holder->camera->wall_x_f
# define WALL_Y_FL holder->camera->wall_y_f
# define PERP_DIST_WALL holder->camera->perp_wall_dist
# define FLOOR_TEX_X (int)(current_floor_x * 64) % 64
# define FLOOR_TEX_Y (int)(current_floor_y * 64) % 64
# define CHECK_SIDE_0 (camera->side == 0 && camera->ray_dir_x > 0)
# define CHECK_SIDE_1 (camera->side == 1 && camera->ray_dir_y < 0)
# define CHECK_SIDE_2 (camera->side == 0 && camera->ray_dir_x < 0)
# define CHECK_SIDE_3 (camera->side == 1 && camera->ray_dir_y > 0)
# define MAP_CELL MAP[camera->map_y][camera->map_x]
# define FPS 1000/holder->frame_time
# define TEX_NUM holder->skybox_num
# define RENDER holder->renderer
# define G holder->gun
# define H holder->gun_1
# define PIC holder->weapon[G]->pic
# define FIXED_POINT_ONE (1 << 8)
# define INT_F(x) ((x) << 8)
# define FLOAT_F(x) ((int)roundf(x * 256))
# define FIXED_I(x) ((x) >> 8)
# define FIXED_F(x) (((float)(x)) / 256)
# define FIX_MULT(x, y) ((x)*(y) >> 8)
# define FIX_DIV(x, y) (((x)<< 8) / (y))
# define IS_SPRITE holder->sprite->is_sprite
# define SHOOTS (*(holder->shoots))
# define ARCADE_TEX holder->sprite->tex_sprite[0]
# define IS_ARC holder->sprite->sprite_found
# define DR_START camera->draw_start
# define MOUSE_Y (holder->height >> 1) - holder->keys.y
# define CHECK_DOWN_X MAP[(int)(P_Y)][(int)(P_X - DIR_X * MOV_SP)]
# define CHECK_LEFT_X MAP[(int)(P_Y)][(int)(P_X - DIR_Y * MOV_SP)]
# define CHECK_RIGHT_X MAP[(int)(P_Y)][(int)(P_X + DIR_Y * MOV_SP)]
# define CHECK_LEFT_Y MAP[(int)(P_Y + DIR_X * MOV_SP)][(int)(P_X)]
# define CHECK_RIGHT_Y MAP[(int)(P_Y - DIR_X * MOV_SP)][(int)(P_X)]
# define CHECK_DOWN_Y MAP[(int)(P_Y - DIR_Y * MOV_SP)][(int)(P_X)]
# define CHECK_UP_X_PLUS2 MAP[(int)(P_Y)][(int)(P_X + DIR_X * MOV_SP) + 2]
# define CHECK_UP_X MAP[(int)(P_Y)][(int)(P_X + DIR_X * MOV_SP)]
# define CHECK_UP_Y MAP[(int)(P_Y + DIR_Y * MOV_SP)][(int)(P_X)]
# define PLANE_Y camera->plane_y
# define ROUND(x) (roundf(x * 10) / 10)
# define V_LEN(x, y) sqrt(x * x + y * y)
# define V_X_NORM(x, y) (x / V_LEN(x, y))
# define V_Y_NORM(x, y) (y / V_LEN(x, y))
# define MAXSPRITES 20

enum				e_adv
{
	jumping,
	flying,
	crouch,
	normal
};

typedef int			t_intfix;

typedef struct		s_mouse
{
	int				x;
	int				y;
}					t_mouse;

typedef struct		s_hud
{
	SDL_Texture		*hud[11];
	int				hp;
	int				ammo;
	int				lives;
	int				rockets;
	int				shield;
	int 			jetpack;
}					t_hud;

typedef struct		s_keys
{
	int				right;
	int				left;
	int				up;
	int				down;
	int				w;
	int				s;
	int				a;
	int				d;
	int				shift;
	int				space;
	int				yrel;
	int				xrel;
	int				x;
	int				y;
	int				f;
	int				lctrl;
}					t_keys;

typedef struct		s_camera
{
	SDL_Surface		*texture[12];
	SDL_Texture		*skybox_tex[5];
	TTF_Font		*font;
	Mix_Chunk		*dstelept;
	float			ray_dir_x;
	float			ray_dir_y;
	float			wall_x_f;
	float			wall_y_f;
	float			side_dist_x;
	float			side_dist_y;
	float			perp_wall_dist;
	float			delta_dist_x;
	float			delta_dist_y;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			camera_x;
	float			camera_y;
	float			plane_y;
	float			time;
	float			old_time;
	float			move_speed;
	float			rot_speed;
	float			wall_x;
	int				step_x;
	int				step_y;
	int				is_hit;
	int				side;
	int				map_x;
	int				map_y;
	int				draw_end;
	int				draw_start;
	int				line_height;
	int			intensity;
}					t_camera;

typedef struct		s_sprite
{
	SDL_Surface		*arr_sprite[2][9];
	SDL_Surface		*tex_sprite[1];
	float			x;
	float			y;
	float			transform_y;
	float			orig_x;
	float			orig_y;
	float			speed;
	int				is_alive;
	int				is_sprite:1;
	int				texture;
	int				draw_start_x;
	int				draw_start_y;
	int				draw_end_x;
	int				draw_end_y;
	int				sprite_width;
	int				sprite_found:1;
}					t_sprite;

typedef struct		s_weapon
{
	SDL_Texture		*texture_sshotgun[29];
	int				num_frames;
	int				frame;
	int				frame_w;
	int				frame_h;
	int				tex_w;
	int				tex_h;
	SDL_Rect		rect;
	int				pic;
	Mix_Chunk		*pistol_shoot;
}					t_weapon;

typedef struct		s_start
{
	SDL_Texture		*start_screen;
	int				play_select;
}					t_start;

typedef struct		s_wolf
{
	float			player_x;
	float			player_y;
	int				height;
	int				width;
	int				skybox_num;
	unsigned int	map_height;
	unsigned int	map_width;
	int				running: 1;
	int				shooting: 1;
	int				jumping: 1;
	float			zbuffer[1024];
	char			**map;
	int 			**height_map;
	SDL_Window		*window;
	SDL_Surface		*image;
	SDL_Texture		*screen;
	SDL_Texture		*texture_ak;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	t_keys			keys;
	t_mouse			mouse;
	t_camera		*camera;
	t_weapon		*weapon[4];
	t_start			*start;
	t_sprite		*sprite;
	t_sprite		*bullet;
	t_hud			*hud;
	unsigned int	fps;
	unsigned int	frame_delay;
	unsigned int	frame_start;
	unsigned int	frame_time;
	Mix_Music		*music;
	int				pause:1;
	int				starting:1;
	int				gun;
	int				gun_1;
	int				*shoots;
	int				frags;
	int				updown;
	int 			extra_updown;
	enum e_adv		advanced;
	int				adv_frames;
	int				start_point;
	int				lifted;
	unsigned int 	shadows:1;
	int 			current_height;
	int 			wall_height;
	unsigned int 	state:1;
}					t_wolf;

void				ft_print_error(char *str);
void				ft_init_image(t_wolf *holder);
void				ft_close_loop(t_wolf *holder, t_camera *camera);
SDL_Surface			*ft_load_bmp(t_wolf *holder, char *path);
SDL_Surface			*ft_load_png(t_wolf *holder, char *path);
void				ft_close(t_wolf *holder);
char				**ft_create_map(char **argv, t_wolf *holder);
void				ft_verify_map(char **map, t_wolf *holder);
void				get_player_coordinates(t_wolf *holder);
void				ft_raycasting(t_wolf *holder, int x);
void				ft_draw_line(int x, int y_start, int y_end, \
								int color, t_wolf *holder);
void				init_weapon(t_weapon *weapon, t_wolf *holder);
void				draw_weapon(t_weapon *weapon[], t_wolf *holder);
void				apply_texture(int x, int y, SDL_Texture *tex, \
								SDL_Renderer *rend);
void				draw_skybox(t_wolf *holder, t_camera *camera);
void				ft_camera_init(t_camera *camera, t_wolf *holder);
SDL_Surface			*load_image(char *path);
SDL_Texture			*load_tex(SDL_Renderer	*renderer, char *path);
void				apply_texture(int x, int y, SDL_Texture *tex, \
								SDL_Renderer *rend);
SDL_Surface			*load_image(char *path);
Mix_Music			*load_music(char *path);
void				draw_fps(t_wolf *holder, TTF_Font *font);
void				draw_text(t_wolf *holder, char *text, int x, int y);
void				ft_start_screen(t_wolf *holder);
Mix_Chunk			*load_chunk(char *path);
void				ft_check_extra_keys(t_wolf *holder, \
					const Uint8 *keystate);
void				draw_floor(t_wolf *holder, t_camera *camera, \
		unsigned int buffer[][holder->width], unsigned int x);
unsigned int		get_pixel(SDL_Surface *surface, int x, int y);
void				ft_draw_sprites(t_wolf *holder, t_camera *camera, \
	unsigned int buffer[][holder->width]);
int					get_sprite_coordinates(t_wolf *holder, char c);
void				ft_move_boss(t_wolf *holder, t_sprite *sprite);
void				ft_check_click(t_wolf *holder);
void				start_game(t_wolf *holder);
void				init_weapon_grenade(t_weapon *weapon, t_wolf *holder);
void				restart_enemy(t_wolf *holder);
void				init_weapon_demon(t_weapon *weapon, t_wolf *holder);
void				init_weapon_shotgun(t_weapon *weapon, t_wolf *holder);
void				draw_score(t_wolf *holder);
void				mouse_move(t_wolf *holder, t_camera *camera, float old);
void				azaporoz_keys_down(t_wolf *holder, t_camera *camera, \
								int key);
void				azaporoz_keys_up(t_wolf *holder, t_camera *camera, \
								int key);
void				azaporoz_action(t_wolf *holder, t_camera *camera);
void				azaporoz_rotate(t_wolf *holder, t_camera *camera, \
									float old);
void				draw_hud(t_wolf *holder);
void				ft_hud_init(t_wolf *holder);
void				ft_check_advanced_move(t_wolf *hold, const Uint8 *keystat);
unsigned int alter_color(unsigned int color, float coefficient);
unsigned int alter_color_fixed(unsigned int color, int coefficient);
#endif
