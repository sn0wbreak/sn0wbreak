<?php
$fdir = $_SERVER['HOME'] . "/.sn0wbreak";
$utils = array("unzip","tar","{$fdir}/ideviceinfo","{$fdir}/partialzip","/os/bin/opensn0w_cli","open","defaults","ssh","bash","php","curl");
foreach($utils as $util)
{
  echo "Checking for {$util}...";
$wut = shell_exec("which {$util}");
if(strlen($wut) == 0)
{
echo " \033[31m [ERROR]\033[0m \n";
die("\033[31m \033[1m Couldn't find {$util}! \033[0m \n");
}
else
{
echo " \033[32m [OK]\033[0m {$wut}";
}
}
