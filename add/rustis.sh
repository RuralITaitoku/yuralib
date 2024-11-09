
set +x
mkdir -p $YURA_HOME/src
cd $YURA_HOME/src
git clone git@github.com:RuralITaitoku/rustis.git

cd $YURA_HOME/src/rustis


if which cargo ; then
    cargo build
else
    echo carugoなし
fi



