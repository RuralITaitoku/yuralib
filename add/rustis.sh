
set +x
mkdir -p $YURA_HOME/prj
cd $YURA_HOME/prj
git clone git@github.com:RuralITaitoku/rustis.git

cd $YURA_HOME/prj/rustis


if which cargo ; then
    cargo build
else
    echo carugoなし
fi



