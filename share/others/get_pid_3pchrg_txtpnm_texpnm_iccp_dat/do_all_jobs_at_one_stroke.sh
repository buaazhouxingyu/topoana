#!/bin/bash
./get_pid_3pchrg_txtpnm_texpnm_dat_temp1.exe
./get_pid_3pchrg_txtpnm_texpnm_iccp_dat_temp1.exe
./get_pid_3pchrg_txtpnm_texpnm_dat_temp2.exe
echo "diff pid_3pchrg_txtpnm_texpnm.dat_temp1 pid_3pchrg_txtpnm_texpnm.dat_temp2"
diff pid_3pchrg_txtpnm_texpnm.dat_temp1 pid_3pchrg_txtpnm_texpnm.dat_temp2
awk '{if($5==0) print $0}' pid_3pchrg_txtpnm_texpnm_iccp.dat_temp1
cp pid_3pchrg_txtpnm_texpnm_iccp.dat_temp1 pid_3pchrg_txtpnm_texpnm_iccp.dat_temp2
#./get_pid_3pchrg_txtpnm_texpnm_iccp_dat.exe
echo "diff pid_3pchrg_txtpnm_texpnm_iccp.dat_temp1 pid_3pchrg_txtpnm_texpnm_iccp.dat_temp2"
diff pid_3pchrg_txtpnm_texpnm_iccp.dat_temp1 pid_3pchrg_txtpnm_texpnm_iccp.dat_temp2
#./awk '{if($5==0) print $0}' pid_3pchrg_txtpnm_texpnm_iccp.dat
exit 0
