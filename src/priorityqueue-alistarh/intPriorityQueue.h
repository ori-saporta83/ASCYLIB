/*   
 *   File: intPriorityQueue.h
 *   Author: Vincent Gramoli <vincent.gramoli@sydney.edu.au>, 
 *  	     Vasileios Trigonakis <vasileios.trigonakis@epfl.ch>
 *  	     Egeyar Ozlen Bagcioglu <egeyar.bagcioglu@epfl.ch>
 *   Description: 
 *   intPriorityQueue.h is part of ASCYLIB
 *
 * Copyright (c) 2014 Vasileios Trigonakis <vasileios.trigonakis@epfl.ch>,
 * 	     	      Tudor David <tudor.david@epfl.ch>
 *	      	      Distributed Programming Lab (LPD), EPFL
 *
 * ASCYLIB is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "alistarh.h"

sval_t pq_contains(sl_intset_t *set, skey_t key);
int pq_insert(sl_intset_t *set, skey_t key, sval_t val);
sval_t pq_deleteMin(sl_intset_t *set);
