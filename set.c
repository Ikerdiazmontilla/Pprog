/**
 * @brief It implements the set module
 *
 * @file set.c
 * @author Fernando Pina
 * @version 0
 * @date 04-02-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"
#include "types.h"


/**
 * @brief set
 *
 * This struct stores all the information of a set.
 */
struct _Set {
  Id id[200]; //static array of ids
  int n_ids; //it saves the numbers of ids 
};


Set* set_create()
{   
    Set *new_set = NULL;
    int i = 0;
    
    
    new_set = (Set*)malloc(sizeof(Set));
    if (new_set == NULL)
    {
        return NULL;
    }
    
    new_set->n_ids = 0;
    for ( ; i < new_set->n_ids; i++)
    {
        new_set->id[i] = NO_ID;
    }
    
    return new_set;
}

Status set_destroy(Set *set)
{
    if (!(set))
    {
        return ERROR;
    }

    free(set);
    return OK;
    
}

Status set_add_id(Set *set ,Id id)
{
    if (!(set) || id == NO_ID)
    {
        return ERROR;
    }
    
    set->id[set->n_ids] = id;
    set->n_ids++;
    return OK;
}

Status set_del_id(Set *set ,Id id)
{
    int i = 0;
    int pos = -1;

    if (!(set) || id == NO_ID || set->n_ids <= 0)
    {
        return ERROR;
    }

    for (i = 0; i < set->n_ids; i++)
    {
        if (set->id[i] == id)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        return ERROR;
    }

    for (i = pos; i < set->n_ids - 1; i++)
    {
        set->id[i] = set->id[i + 1];
    }

    set->n_ids--;
    set->id[set->n_ids] = NO_ID;

    return OK;
}


Bool set_find_id(Set *set, Id id)
{   
    int i = 0;
    if (!(set) || id == NO_ID)
    {
        return FALSE;
    
    }

    for (; i < set->n_ids; i++)
    {
        if (set->id[i] == id)
        {
            return TRUE;
        }
        
    }

    return FALSE;

}

Status set_print(Set *set)
{   
    int i = 0;
    if (!(set))
    {
        return ERROR;
    }
    
    for ( i ; i < set->n_ids; i++)
    {
        fprintf(stdout, "--> (Id: %ld;)\n", set->id[i]);
    }
    
    return OK;

}


int set_get_n_ids(Set *set)
{
    if (set == NULL)
    {
        return -1;
    }
    
    return set->n_ids;
    
}



Id *set_get_ids(Set *set)
{
    if (!(set))
    {
        return NULL;
    }
    
    return set->id;
}

