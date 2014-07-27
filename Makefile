# Compiling with g++
ifndef icc
CC=g++
LD=g++
endif

# Compiling with icc
ifdef icc
CC=icc
LD=icc
endif

# Compiling parameters
cparams:=-O3 -Wall
lparams:=-lm -O3 -Wall

# Optimization
ifdef noopt
cparams:=-Wall
lparams:=-lm -Wall
endif

# Debugging
ifdef debug
cparams:=$(cparams) -g
lparams:=$(lparams) -g
endif

# Profiling
ifdef profiling
cparams:=$(cparams) -pg -fprofile-arcs -ftest-coverage
lparams:=$(lparams) -pg -fprofile-arcs -ftest-coverage
endif

CPPFLAGS=$(cparams)

# The directories that contain .cpp and .hpp files
dirs:= Defs Calc Ranmar Random Test Cls Vector Matrix Text \
	Calendar Fractal Util Point String PriorityQueue Sort

alldirs:=. $(dirs)

VPATH:=$(foreach dir,$(dirs),$(dir):).

include $(foreach dir,$(alldirs),$(wildcard $(dir)/*.d))

# Sources and objects
sources:=$(foreach dir,$(alldirs),$(wildcard $(dir)/*.cpp))
objects:=$(sources:.cpp=.o)

.PHONY: calc ranmar random cls vector matrix text calendar fractal \
	str pq heapsort

all: calc ranmar random cls vector matrix text calendar fractal \
	str pq heapsort

objs: $(objects)

dep: savings $(sources:.cpp=.d)
	@echo Depencies made..

# Executables...

mkfmt: savings mkfmt.exe
	@echo Executable mkfmt.exe made.

mkfmt.exe: mkfmt.o

free_db_key: savings free_db_key.exe
	@echo Executable free_db_key.exe made.

free_db_key.exe: free_db_key.o

musicbrainz_key: savings musicbrainz_key.exe
	@echo Executable musicbrainz_key.exe made.

musicbrainz_key.exe: musicbrainz_key.o

str: savings str.exe
	@echo Executable str.exe made.

str.exe: util.o str.o

test: savings test.exe
	@echo Executable test.exe made.

test.exe: util.o ranmar.o random.o cls.o vector.o matrix.o alg.o test.o \
	item.o pq.o

heapsort: savings heapsort.exe
	@echo Executable heapsort.exe made.

heapsort.exe: util.o vector.o heapsort.o

mkpq: savings mkpq.exe
	@echo Executable mkpq.exe made.

mkpq.exe: util.o ranmar.o random.o vector.o item.o pq.o mkpq.o

text: savings text.exe
	@echo Executable text.exe made.

text.exe: text.o

calendar: savings calendar.exe
	@echo Executable calendar.exe made.

calendar.exe: calendar.o

fractal: savings fractal.exe
	@echo Executable fractal.exe made.

fractal.exe: ranmar.o random.o vector.o matrix.o alg.o util.o point.o \
	fractal.o

#Check for unsaved files
savings:
	@! (find | grep -e .\#) || ( ! echo Warning: above files are not saved!)
	@echo All sources ok.

#Remove all
freespace: cleanall
	@echo -n Removing backups...
	@rm -f `find | grep ~$$`
	@rm -f `find | grep /\#.*\#$$`
	@echo OK

#Use to remove also depencies
cleanall: cleanDep.pat
	@echo -n Removing objects, output and depencies...
	@rm -f `find | grep -f clean.pat` clean.pat
	@echo OK

#Remove object files
cl: clean.pat
	@echo -n Removing objects...
	@rm -f `find | grep -f clean.pat` clean.pat
	@echo OK

#Remove objects and exe files
clean: cleanEx.pat
	@echo -n Removing objects and output...
	@rm -f `find | grep -f clean.pat` clean.pat
	@echo OK

cleanEx.pat : clean.pat
	@echo [.]ex$$ >> clean.pat

cleanDep.pat : clean.pat
	@echo [.]d$$ >> clean.pat

clean.pat:
	@echo [.]out$$ > clean.pat
	@echo [.]o$$ >> clean.pat
	@echo [.]bbg$$ >> clean.pat
	@echo [.]bb$$ >> clean.pat
	@echo [.]da$$ >> clean.pat
	@echo [.]gcov$$ >> clean.pat
	@echo [.]c~$$ >> clean.pat
	@echo [.]h~$$ >> clean.pat

%.d : %.cpp
	@echo -n Making depencies for $<...
	@cd $(<D) ; set -e; $(CC) -MM $(cparams) $(<F) \
	| sed 's|\($(*F)\)\.o[ :]*|\1.o $(@F)\ : |g' > $(@F); \
	[ -s $(@F) ] || rm -f $(@F)
	@echo OK

%.o : %.cpp %.d
	@echo -n Compiling $<...
	@$(CC) $(cparams) -c $< -o $(<D)/$(@F)
	@echo OK

dependingObjects=$(filter $(addprefix %/,$(^F)),$(objects)) $(filter-out %.o,$^)

%.exe : %.o 
	@echo -n Linking object files...
	@$(LD) $(lparams) $(dependingObjects) -o $@
	@echo OK
