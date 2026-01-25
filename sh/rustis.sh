
export PRJ=rustis
export PRJ_REP=git@github.com:RuralITaitoku/rustis.git
set +x
mkdir -p $YURA_HOME/prj
cd $YURA_HOME/prj
git clone $PRJ_REP

cd $YURA_HOME/prj/$PRJ

if which cargo ; then
    cargo build
else
    echo cargoなし
fi





