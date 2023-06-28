echo "echo Restoring environment" > "/home/simi/Dev/game-of-life/deactivate_conanrunenv-release-x86_64.sh"
for v in ALSA_CONFIG_DIR
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "/home/simi/Dev/game-of-life/deactivate_conanrunenv-release-x86_64.sh"
    else
        echo unset $v >> "/home/simi/Dev/game-of-life/deactivate_conanrunenv-release-x86_64.sh"
    fi
done


export ALSA_CONFIG_DIR="/home/simi/.conan2/p/libalc18832b4760c0/p/res/alsa"