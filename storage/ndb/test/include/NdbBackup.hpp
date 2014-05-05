/* Copyright (c) 2003-2005 MySQL AB


   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA */


#ifndef NDBT_BACKUP_HPP
#define NDBT_BACKUP_HPP

#include <mgmapi.h>
#include <Vector.hpp>
#include "NdbConfig.hpp"
#include <NdbRestarter.hpp>

class NdbBackup : public NdbConfig {
public:
  NdbBackup(const char* _addr = 0)
    : NdbConfig(_addr) {};

  int start(unsigned & _backup_id,
	    int flags = 2,
	    unsigned int user_backup_id= 0,
	    unsigned int logtype= 0);
  int start() { unsigned unused =0; return start(unused); }
  int restore(unsigned _backup_id, bool restore_meta = true);

  int NFMaster(NdbRestarter& _restarter);
  int NFMasterAsSlave(NdbRestarter& _restarter);
  int NFSlave(NdbRestarter& _restarter);
  int NF(NdbRestarter& _restarter, int *NFDuringBackup_codes, const int sz, bool onMaster);

  int FailMaster(NdbRestarter& _restarter);
  int FailMasterAsSlave(NdbRestarter& _restarter);
  int FailSlave(NdbRestarter& _restarter);
  int Fail(NdbRestarter& _restarter, int *Fail_codes, const int sz, bool onMaster);
  int startLogEvent();
  int checkBackupStatus();

  int clearOldBackups();
  int abort(unsigned _backup_id);

private:

  int execRestore(bool _restore_data,
		  bool _restore_meta,
		  int _node_id,
		  unsigned _backup_id);

  const char * getBackupDataDirForNode(int _node_id);
  NdbLogEventHandle log_handle;
  
};

#endif
