
set -x
export YURA_HOME=/mnt/c/Users/yurur/relax/yuralib
if [ "$1" = "add" ]; then
	echo $YURA_HOME
	mkdir -p $YURA_HOME/src
	cd $YURA_HOME/src
	if [ "$2" = "ruralis2" ]; then
		echo test
		pwd
		ls
	fi
fi
