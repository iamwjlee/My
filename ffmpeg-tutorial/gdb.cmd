#souce my.cmd
define run_ff
	file ./bin/tutorial02.out
	b main
	r http://192.168.0.37:8080/genitek/2.avi
#	continue
end

run_ff
