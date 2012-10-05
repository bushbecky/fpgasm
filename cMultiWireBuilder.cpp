/******************************************************************************
 Copyright 2012 Victor Yurkovsky

    This file is part of FPGAsm

    FPGAsm is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FPGAsm is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FPGAsm.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/
#include "global.h"
#include "cMultiWireBuilder.h"
#define CLASS cMultiWireBuilder 
CLASS::CLASS(){
  max = CMULTIWIRE_CAP_INIT;    //initial limit, in wireends.
  buf = (sWireEnd*)malloc(max*sizeof(sWireEnd));
}

CLASS::~CLASS(){
 //we never free the buffer - it is used by consumers.
}

void CLASS::add(int inst,int port,int busid){
  //is there room 
  if(index>=max) {
    // reallocate, double size
fprintf(stderr,"cWires: reallocating from %d to %d\n",max,max*2);
    max = max*2;
    buf = (sWireEnd*)realloc(buf,max*sizeof(sWireEnd));
  }
  buf[index].inst=inst;
  buf[index].pindex=port;
  buf[index].busid=busid;
  index++;
}
void CLASS::stop(){
  buf[index].inst=INST_STOP;
  index++;
}
void CLASS::end(){
  buf[index].inst=INST_END;
  index++;
}
void CLASS::solidify(){
  end();
  buf = (sWireEnd*)realloc(buf,index*sizeof(sWireEnd));
}


  