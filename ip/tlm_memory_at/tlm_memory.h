/********************************************************************************
        MPSoCBench Benchmark Suite
        Authors: Liana Duenha
        Supervisor: Rodolfo Azevedo
        Date: July-2012
        www.archc.org/benchs/mpsocbench

        Computer Systems Laboratory (LSC)
        IC-UNICAMP
        http://www.lsc.ic.unicamp.br/


        This source code is part of the MPSoCBench Benchmark Suite, which is a
free
        source-code benchmark for evaluation of Electronic Systemc Level
designs.
        This benchmark is distributed with hope that it will be useful, but
        without any warranty.

*********************************************************************************/

/**
 * @file      tlm_memory.h
 * @author    Bruno de Carvalho Albertini
 *	      Liana Duenha
 * @author    The ArchC Team
 *            http://www.archc.org/
 *
 *            Computer Systems Laboratory (LSC)
 *            IC-UNICAMP
 *            http://www.lsc.ic.unicamp.br/
 *
 * @version
 * @date      Sun, 02 Apr 2006 08:07:46 -0200
 * @brief     Defines a ac_tlm memory.
 *

 * @date      Wed, 22 Oct 2012
 * @brief     Defines a TLM 2.0 memory
 *
 * @attention Copyright (C) 2002-2005 --- The ArchC Team
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef TLM_MEMORY_H_
#define TLM_MEMORY_H_

//////////////////////////////////////////////////////////////////////////////

// Standard includes
// SystemC includes

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"
#include <tlm.h>
#include "tlm_utils/simple_target_socket.h"

#include "../../defines.h"

#include "IniReader.h"

#ifdef DRAMSIM2
#include "DRAMSim.h"
using namespace DRAMSim;
#endif

/// Namespace to isolate memory from ArchC

namespace user {

/// A TLM memory
class tlm_memory : public sc_module {

public:
  tlm_utils::simple_target_socket<tlm_memory> LOCAL_target_socket;

  tlm_memory(sc_module_name module_name, unsigned int i,
             unsigned int k); // = 536870912);

  ~tlm_memory();

  void b_transport(ac_tlm2_payload &, sc_core::sc_time &);

  unsigned int start_address() const;
  unsigned int end_address() const;

  /* memory direct access functions  - useful to load the application in memory
   */

  ac_tlm_rsp_status read(unsigned int address, unsigned int size,
                         unsigned char *data);
  ac_tlm_rsp_status write(unsigned int address, unsigned int size,
                          const unsigned char *data);

#ifdef DRAMSIM2
  void printStatus(FILE *, bool = false, bool = false) const;
#endif

private:
  uint8_t *memory;
  unsigned int m_start_address;
  unsigned int m_end_address;

  ac_tlm_rsp_status writem(const uint32_t &, const unsigned char *,
                           unsigned int);
  ac_tlm_rsp_status readm(const uint32_t &, unsigned char *, unsigned int);

  vector<unsigned int> processorsReads;
  vector<unsigned int> processorsWrites;

#ifdef DRAMSIM2
  MultiChannelMemorySystem *DRAMSim_mem;
  void alignTransactionAddress(uint64_t &);
#endif
};
};

#endif // TLM_MEMORY_H_
