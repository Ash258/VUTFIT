FILES = solution.m getmaxfreq.m hist2opt.m
CLEAN = result/* solution.zip *.aux *.log *.out *.synctex.gz *.fls *.fdb_latexmk

.PHONY: all

all: clean
	matlab -r "run('solution.m')"

clean:
	rm -rf $(CLEAN)

zip:
	zip solution.zip $(FILES)

ssh:
	ssh -X xcaber00@merlin.fit.vutbr.cz

upload:
	scp $(FILES) Makefile xcaber00@merlin.fit.vutbr.cz:~/Projekty/ISS

# make download args="task2.png,task6.png,..."
download:
	scp xcaber00@merlin.fit.vutbr.cz:~/Projekty/ISS/result/\{$(args)\} Final/.
