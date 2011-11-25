/**
 * C Object System
 * COS contract
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cos/Object.h>
#include <cos/gen/object.h>
#include <cos/gen/message.h>

static int cos_contract_level_ = COS_CONTRACT_POST;

// ----- invariant set/unset

int
cos_contract_setLevel(int lvl)
{
  int old = cos_contract_level_;

  if (lvl >= COS_CONTRACT_NO && lvl <= COS_CONTRACT_ALL)
    cos_contract_level_ = lvl;
  
  return old;
}

// ----- invariant

void
cos_contract_invariant1(OBJ _1, STR file, int line)
{
  if (cos_contract_level_ < COS_CONTRACT_ALL) return;
  
  if (gunderstandMessage1(_1, genericref(ginvariant)) == True)
    ginvariant(_1,file,line);
}

void
cos_contract_invariant2(OBJ _1, OBJ _2, STR file, int line)
{
  if (cos_contract_level_ < COS_CONTRACT_ALL) return;

  cos_contract_invariant1(_1,file,line);
  cos_contract_invariant1(_2,file,line);
}

void
cos_contract_invariant3(OBJ _1, OBJ _2, OBJ _3, STR file, int line)
{
  if (cos_contract_level_ < COS_CONTRACT_ALL) return;

  cos_contract_invariant1(_1,file,line);
  cos_contract_invariant1(_2,file,line);
  cos_contract_invariant1(_3,file,line);
}

void
cos_contract_invariant4(OBJ _1, OBJ _2, OBJ _3, OBJ _4, STR file, int line)
{
  if (cos_contract_level_ < COS_CONTRACT_ALL) return;

  cos_contract_invariant1(_1,file,line);
  cos_contract_invariant1(_2,file,line);
  cos_contract_invariant1(_3,file,line);
  cos_contract_invariant1(_4,file,line);
}

void
cos_contract_invariant5(OBJ _1, OBJ _2, OBJ _3, OBJ _4, OBJ _5, STR file, int line)
{
  if (cos_contract_level_ < COS_CONTRACT_ALL) return;

  cos_contract_invariant1(_1,file,line);
  cos_contract_invariant1(_2,file,line);
  cos_contract_invariant1(_3,file,line);
  cos_contract_invariant1(_4,file,line);
  cos_contract_invariant1(_5,file,line);
}

