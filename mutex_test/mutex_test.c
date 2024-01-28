/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:10:13 by kprigent          #+#    #+#             */
/*   Updated: 2024/01/28 19:32:07 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_test
{
	struct s_data *data;
	pthread_mutex_t mutex_0;
	pthread_mutex_t mutex_1;
	
}	t_test;

typedef struct s_data
{
	t_test *philosophe;
	pthread_t *thread_id;
	
}	t_data;

void *action(void *arg)
{
	t_data *data = (t_data *)arg;
	
  	pthread_mutex_lock(&(data->philosophe[0].mutex_0));
    printf("thread passe\n");
    //pthread_mutex_unlock((&data->philosophe[0].mutex_0));
    return NULL;
}

int main(void)
{
    t_data data;

    data.thread_id = malloc(sizeof(pthread_t) * 2);
    data.philosophe = malloc(sizeof(t_test) * 2);

    pthread_mutex_init(&(data.philosophe[0].mutex_0), NULL);
    pthread_mutex_init(&(data.philosophe[0].mutex_1), NULL);

    pthread_create(&(data.thread_id[0]), NULL, action, (void*)&data);
    pthread_join(data.thread_id[0], NULL);

    pthread_create(&(data.thread_id[1]), NULL, action, (void*)&data);
    pthread_join(data.thread_id[1], NULL);

    free(data.thread_id);
    free(data.philosophe);

    return 0;
}