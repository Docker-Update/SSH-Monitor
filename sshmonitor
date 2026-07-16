#!/bin/bash

case "$1" in
    start)
        echo "Activation..."
        systemctl start ssh-monitor
        ;;
    stop)
        echo "Deactivation..."
        systemctl stop ssh-monitor
        ;;
    restart)
        echo "Redémarrage..."
        systemctl restart ssh-monitor
        ;;
    status)
        systemctl status ssh-monitor
        ;;
    *)
        echo "Usage: $0 {start|stop|restart|status}"
        exit 1
        ;;
esac