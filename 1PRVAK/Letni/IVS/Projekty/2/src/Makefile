all: clean
	../gradlew -p .. build

pack: clean
	../gradlew -p .. archiveZip

clean:
	../gradlew -p .. clean

test: clean
	../gradlew -p .. test

doc:
	../gradlew -p .. doxygen

run: all
	../gradlew -p .. runJar
