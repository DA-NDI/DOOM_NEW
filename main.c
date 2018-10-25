/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolgin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 18:24:47 by avolgin           #+#    #+#             */
/*   Updated: 2018/10/23 23:38:06 by avolgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void		ft_close(t_wolf *holder)
{
	Mix_FreeChunk(holder->weapon[0]->pistol_shoot);
	Mix_FreeChunk(holder->weapon[1]->pistol_shoot);
	holder->weapon[0]->pistol_shoot = NULL;
	holder->weapon[1]->pistol_shoot = NULL;
	SDL_DestroyRenderer(holder->renderer);
	SDL_DestroyWindow(holder->window);
	holder->running = 0;
	free(holder->start);
	TTF_Quit();
	SDL_Quit();
	system("leaks doom-nukem");
	exit(0);
}

void		ft_print_error(char *str)
{
	ft_putendl(str);
	system("leaks doom-nukem");
	exit(1);
}

t_wolf		*holder_init(t_wolf *holder)
{
	holder->height = 768;
	holder->width = 1024;
	holder->running = 1;
	holder->shooting = 0;
	holder->advanced = normal;
	holder->fps = 60;
	holder->pause = 0;
	holder->starting = 1;
	holder->frame_delay = 15;
	holder->skybox_num = 0;
	holder->gun = 0;
	holder->frags = 0;
	holder->updown = 0;
	holder->adv_frames = 0;
	holder->start_point = 0;
	holder->lifted = 0;
	holder->extra_updown = 0;
	holder->shadows = 0;
	holder->state = 0;
	holder->sprite_tex = (t_sprite_tex**)malloc(sizeof(t_sprite_tex*) * 7);
	holder->sprite = (t_sprite**)malloc(sizeof(t_sprite*) * 22);
	holder->retry_state = 0;
	holder->ceiling = 1;
	return (holder);
}

t_sprites 		*ft_sort_sprites_init(void)
{
	t_sprites 	*s_sorted;

	s_sorted = (t_sprites*)malloc(sizeof(t_sprites));
	s_sorted->order = malloc(sizeof(int) * 25);
	s_sorted->dist = malloc(sizeof(float) * 25);
	s_sorted->num = 0;

	return (s_sorted);
}

void 		ft_sort_sprites_put(t_wolf *holder, t_sprites *s_sorted, int num)
{
	int			a;

	a = -1;
	while (++a < holder->sprite_tex[0]->amount && a < 3)
		s_sorted->all_sprites[num++] = CAR;
	a = -1;
	while (++a < holder->sprite_tex[2]->amount && a < 5)
		s_sorted->all_sprites[num++] = ARC;
	a = -1;
	while (++a < holder->sprite_tex[6]->amount && a < 3)
		s_sorted->all_sprites[num++] = KOLA;
	a = -1;
	while (++a < holder->sprite_tex[5]->amount && a < 3)
		s_sorted->all_sprites[num++] = PEPSI;
	a = -1;
	while (++a < holder->sprite_tex[4]->amount && a < 3)
		s_sorted->all_sprites[num++] = POT;
	a = -1;
	while (++a < holder->sprite_tex[3]->amount && a < 3)
		s_sorted->all_sprites[num++] = AMO;
	s_sorted->num = num;
}

void		start_game(t_wolf *holder)
{
	holder_init(holder);
	holder->line[0].x1 = 100;
	holder->line[0].y1 = 100;
	holder->line[0].x2 = 500;
	holder->line[0].y2 = 100;
	holder->line[1].x1 = 500;
	holder->line[1].y1 = 100;
	holder->line[1].x2 = 300;
	holder->line[1].y2 = 300;
	holder->line[2].x1 = 300;
	holder->line[2].y1 = 300;
	holder->line[2].x2 = 100;
	holder->line[2].y2 = 100;
	get_player_coordinates(holder, 'P');
	ft_init_image(holder);
	ft_hud_init(holder);
	ft_start_screen(holder);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	holder->sprites = ft_sort_sprites_init();
	ft_sort_sprites_put(holder, holder->sprites, 0);
	ft_raycasting(holder, 0);
}

int			main(int argc, char **argv)
{
	static t_wolf	holder[1];
	char			*map_name;

	if (argc != 2 || !argv[1] || ft_strlen(argv[1]) > 30) //|| system("tar -xzf package"))
		ft_print_error("Usage: \
		./doom-nukem <1-5 for level, or name of custom map>");
	map_name = ft_strsub("./maps/", 0, 50);
	map_name = ft_strcat(map_name, argv[1]);
	holder->map = ft_create_map(map_name, holder);
	ft_verify_map(holder->map, holder);
	start_game(holder);
	return (0);
}
