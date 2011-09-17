#line 1 "source/shader.c"
/*
 * shader.c
 *
 * Copyright (C) an0nym0us
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 *
 */

#include <stdio.h>
#include <string.h>

#include "common.h"
#include "debug.h"
#include "shader.h"

#include "shader_vpo.h"
#include "shader_fpo.h"


void
shaderInitialization (shaderData *vf)
{
  dbgprintf ( "initializing" ) ;

  /* shader variables */
  vf->vert.vpo = (rsxVertexProgram*)shader_vpo ;
  vf->frag.fpo = (rsxFragmentProgram*)shader_fpo ;

  vf->vert.ucode = rsxVertexProgramGetUCode ( vf->vert.vpo ) ;
  vf->frag.ucode = rsxFragmentProgramGetUCode ( vf->frag.fpo, &vf->frag.size ) ;

  vf->frag.buffer = (u32*)rsxMemalign ( 64, vf->frag.size ) ;
  memcpy ( vf->frag.buffer, vf->frag.ucode, vf->frag.size ) ;
  rsxAddressToOffset ( vf->frag.buffer, &vf->frag.offset ) ;

  dbgprintf ( "initialized" ) ;
}

