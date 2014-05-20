<?php
$a = "java -jar " . $_SERVER['HOME'] . "/.sn0wbreak/ssh_rd.jar";
$b = shell_exec("ps | grep \"{$a}\"");
$c = explode("\n",$b)[0];
$d = explode(" ",$c);
shell_exec("kill {$d[1]}");
?>
