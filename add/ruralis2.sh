
export PRJ=ruralis2
export PRJ_REP=git@github.com:RuralITaitoku/ruralis2.git
set +x
mkdir -p $YURA_HOME/prj
cd $YURA_HOME/prj
git clone $PRJ_REP

cd $YURA_HOME/prj/$PRJ

make



