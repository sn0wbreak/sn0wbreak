<?php
$a = "java -jar " . $_SERVER['HOME'] . "/.sn0wbreak/ssh_rd.jar";
$b = shell_exec("ps | grep \"{$a}\"");
$c = explode("\n",$b);
$c = $c[0];
$d = explode(" ",$c);
shell_exec("kill {$d[1]}");
shell_exec("kill {$d[0]}");
?>
