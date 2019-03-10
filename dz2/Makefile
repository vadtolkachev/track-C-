CXX=g++-8
LD=$(CXX)
WARFLAGS=-Wall -Wextra -Wpedantic -Wconversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Walloc-zero
WARFLAGSALL=-Wabi-tag -Waddress -Waggregate-return -Waggressive-loop-optimizations -Walloc-zero -Walloca -Warray-bounds -Wattributes -Wbool-compare -Wbool-operation -Wbuiltin-declaration-mismatch -Wbuiltin-macro-redefined -Wc++11-compat -Wc++14-compat -Wc++1z-compat -Wcast-align -Wcast-qual -Wchar-subscripts -Wchkp -Wclobbered -Wcomment -Wconditionally-supported -Wconversion -Wconversion-null -Wcoverage-mismatch -Wcpp -Wctor-dtor-privacy -Wdangling-else -Wdate-time -Wdelete-incomplete -Wdelete-non-virtual-dtor -Wdeprecated -Wdeprecated-declarations -Wdisabled-optimization -Wdiv-by-zero -Wdouble-promotion -Wduplicated-branches -Wduplicated-cond -Weffc++ -Wempty-body -Wendif-labels -Wenum-compare -Wexpansion-to-defined -Wextra -Wfloat-conversion -Wfloat-equal -Wformat-contains-nul -Wformat-extra-args -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat-y2k -Wformat-zero-length -Wframe-address -Wfree-nonheap-object -Whsa -Wignored-attributes -Wignored-qualifiers -Winherited-variadic-ctor -Winit-self -Winline -Wint-in-bool-context -Wint-to-pointer-cast -Winvalid-memory-model -Winvalid-offsetof -Winvalid-pch -Wliteral-suffix -Wlogical-not-parentheses -Wlogical-op -Wlong-long -Wlto-type-mismatch -Wmain -Wmaybe-uninitialized -Wmemset-elt-size -Wmemset-transposed-args -Wmisleading-indentation -Wmissing-braces -Wmissing-declarations -Wmissing-field-initializers -Wmissing-include-dirs -Wmultichar -Wmultiple-inheritance -Wnamespaces -Wnarrowing -Wnoexcept -Wnoexcept-type -Wnon-template-friend -Wnon-virtual-dtor -Wnonnull -Wnonnull-compare -Wnull-dereference -Wodr -Wold-style-cast -Wopenmp-simd -Woverflow -Woverlength-strings -Woverloaded-virtual -Wpacked -Wpacked-bitfield-compat -Wpadded -Wparentheses -Wpedantic -Wpmf-conversions -Wpointer-arith -Wpointer-compare -Wpragmas -Wpsabi -Wredundant-decls -Wregister -Wreorder -Wrestrict -Wreturn-local-addr -Wreturn-type -Wsequence-point -Wshadow -Wshadow=compatible-local -Wshadow=local -Wshift-count-negative -Wshift-count-overflow -Wshift-negative-value -Wsign-compare -Wsign-conversion -Wsign-promo -Wsized-deallocation -Wsizeof-array-argument -Wsizeof-pointer-memaccess -Wstack-protector -Wstrict-null-sentinel -Wsubobject-linkage -Wsuggest-attribute=const -Wsuggest-attribute=format -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch -Wswitch-bool -Wswitch-default -Wswitch-enum -Wswitch-unreachable -Wsync-nand -Wsynth -Wsystem-headers -Wtautological-compare -Wterminate -Wtrampolines -Wtrigraphs -Wtype-limits -Wundef -Wuninitialized -Wunknown-pragmas -Wunsafe-loop-optimizations -Wunused -Wunused-but-set-parameter -Wunused-but-set-variable -Wunused-function -Wunused-label -Wunused-local-typedefs -Wunused-macros -Wunused-parameter -Wunused-result -Wunused-value -Wunused-variable -Wuseless-cast -Wvarargs -Wvariadic-macros -Wvector-operation-performance -Wvirtual-inheritance -Wvirtual-move-assign -Wvla -Wvolatile-register-var -Wwrite-strings -Wzero-as-null-pointer-constant
COVFLAGS=-fprofile-arcs -ftest-coverage
CXXFLAGS=$(WARFLAGS) -O3 -g -MD
LDFLAGS=$(CXXFLAGS)
OBJFILES=test.o

all: test.x

test.x: $(OBJFILES)
	$(LD) $(LDFLAGS) -o test.x $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean_data:
	rm -rf *.gcda *.log *.info covinfo *.gcov

clean: clean_data
	rm -rf test.x *.o *.d *.gcno

-include *.d