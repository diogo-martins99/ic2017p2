#include <stdio.h>
#include <time.h>
#include "showworld.h"
#include "simple_showworld.h"

/* Horizontal world size */
#define WORLD_X 5

/* Vertical world size */
#define WORLD_Y 5

typedef struct {
  AGENT_TYPE type; // agent type
  unsigned char playable; // Is agent playable?
  unsigned short id; // Agent ID
} AGENT;

typedef struct {
  AGENT *grid; // World is a grid composed of agents
  unsigned int xsize; // Horizontal world size.
  unsigned int ysize; // Vertical world size.
} WORLD;

unsigned int get_ag_info(void *world, unsigned int x, unsigned int y);

int main() {
  /* An instance of a WORLD structure. */
  WORLD my_world;

  /* A bidimensional array of agents, representing agents in a grid */
  AGENT agent_grid[WORLD_X][WORLD_Y];

  /* Number of agents created */
  unsigned int nagents = 0;

  /* Initialize random number generator seed */
  srand(time(NULL));

  /* Cycle through all cells in grid and randomly place agents in it */
  for (int i = 0; i < WORLD_X; i++) {
    for (int j = 0; j < WORLD_Y; j++) {

      /* Possible agent in grid */
      AGENT ag = {None, 0, 0};

      /* Obtain a probability between 0 and 99. */
      unsigned char probability = rand() % 100;

      /* There is a 10% probability of creating an agent. */
      if (probability <= 9) {

        /* IF we got here, an agent will be placed at (i, j). */

        /* Randomly define agent type. */
        ag.type = (rand() % 2 == 0) ? Human : Zombie;

        /* Give 10% probability of agent being playable by user */
        ag.playable = (rand() % 10 == 0);

        /* Assign agent ID and then increment number of agents so far */
        ag.id = nagents++;
      }

      /* Assign possible agent to grid at (i,j). */
      agent_grid[i][j] = ag;
    }
  }

  /* Populate the my_world variable. */
  /* Bidimensional array of agents as a pointer to agents. */
  my_world.grid = (AGENT *) agent_grid;

  /* World size is defined by constants. */
  my_world.xsize = WORLD_X;
  my_world.ysize = WORLD_Y;

  /* Show world using the simple_show_world() function.
  This function can be used in the first part of the project */

  simple_showworld(&my_world, WORLD_X, WORLD_Y, get_ag_info)
    return 0;
}




unsigned int get_ag_info(void *world, unsigned int x, unsigned int y) {

    /* The agent information to return. */
    unsigned int ag_info = 0;

    /* Convert generic pointer to world to a WORLD object. */
    WORLD *my_world = (WORLD *) world;

    /* Check if the given (x,y) coordinates are within bounds of the world. */
    if ((x >= my_world->xsize) || (y >= my_world->ysize)) {

        /* If we got here, then the coordinates are off bounds. As such we will
           report that the requested agent is of unknown type. No need to
           specify agent ID or playable status, since the agent is unknown. */
        ag_info = Unknown;

    } else {

        /* Given coordinates are within bounds, let's get and pack the request
           agent information. */

        /* Obtain agent at specified coordinates. */
        AGENT ag = my_world->grid[x * my_world->xsize + y];

        /* Is there an agent at (x,y)? */
        if (ag.type == None) {

            /* If there is no agent at the (x,y) coordinates, set agent type to
               None. No need to specify agent ID or playable status, since
               there is no agent here. */
            ag_info = None;

        } else {

            /* If we get here it's because there is an agent at (x,y). Bit-pack
               all the agent information as specified by the get_agent_info_at
               function pointer definition. */
            ag_info = (ag.id << 3) | (ag.playable << 2) | ag.type;

        }

    }

    /* Return the requested agent information. */
    return ag_info;
}
