/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:36:29 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/09/16 14:40:44 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	play_audio(char *path, char *volume)
{
	execl("/usr/bin/afplay", "afplay", path, "-v", volume);
}

static void	play_sound(int type)
{
	pid_t	pid;
	int		status;
	int		door;

	pid = fork();
	if (pid == 0)
	{
		if (type == MUSIC)
			play_audio("audio/quake_track_4.m4a", "0.25");
		else if (type == TORCH_ON)
			play_audio("audio/torchlight_on.m4a", "1");
		else if (type == TORCH_OFF)
			play_audio("audio/torchlight_off.m4a", "1");
		else if (type == DOORS)
		{
			door = rand() % 3;
			if (door == 0)
				play_audio("audio/door_open1.m4a", "1");
			if (door == 1)
				play_audio("audio/door_open2.m4a", "1");
			if (door == 2)
				play_audio("audio/door_open3.m4a", "1");
		}
	}
	waitpid(pid, &status, 0);
}

static void	*audio_controller(void *arg)
{
	t_audio	*audio;

	audio = (t_audio *)arg;
	while (1)
	{
		if (audio->type == MUSIC)
			play_sound(audio->type);
		if ((audio->type == TORCH_ON || audio->type == TORCH_OFF
				|| audio->type == DOORS) && audio->play == 1)
		{
			play_sound(audio->type);
			audio->play = 0;
		}
	}
	return (NULL);
}

void	audio_init(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cub->audios[i].type = i;
		cub->audios[i].play = 0;
		pthread_create(&cub->audios[i].tid, NULL,
			audio_controller, &cub->audios[i]);
		i++;
	}
}
