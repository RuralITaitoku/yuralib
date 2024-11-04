
set -x
# export YURA_HOME=/mnt/c/Users/yurur/relax/yuralib
echo $YURA_HOME
if [ "$1" = "add" ]; then
	echo $YURA_HOME
	mkdir -p $YURA_HOME/src
	cd $YURA_HOME/add
	set +x
	. $2".sh"
fi
