#nice -n -20 python3 ./monitor.py
#sleep 2 && bash -c "source ./run-parts"
#kill -9
#tail -f /var/log/dmesg
#htop

import psutil
import time

def monitor_and_kill_process():
    for proc in psutil.process_iter(['name', 'cpu_percent', 'create_time']):
        create_time = proc.info['create_time']
        current_time = time.time()
        uptime = current_time - create_time
        if proc.info['cpu_percent'] > 30:
            print(uptime, proc.info)

        if 'bash' not in proc.info['name']:
            continue

        if proc.info['cpu_percent'] > 60:
            proc.kill()
            print("is killed")

if __name__ == "__main__":
    while True:
        monitor_and_kill_process()
        time.sleep(0.5)

