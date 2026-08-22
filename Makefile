NAME		=	models
VERSION		=	1.0.0
ENV			=	

PACKAGES	=	tbaricault_templates	\
				tbaricault_uniconvert

TARGETS		=	tbaricault::templates	\
				tbaricault::uniconvert

SRC			=	BaseElement	\
				BaseModel

all: build

configure:
	@cmake							\
		-B build 					\
		-DNAME="$(NAME)"			\
		-DVERSION="$(VERSION)"		\
		-DENV="$(ENV)"				\
		-DPACKAGES="$(PACKAGES)"	\
		-DTARGETS="$(TARGETS)"		\
		-DSRC="$(SRC)"

build: configure
	@cmake --build build

clean:
	@rm -dfr build

re: clean build

install: build
	@cmake --install build
	@cmake -P cmake/generate_uninstall.cmake

uninstall:
	@cmake -P uninstall.cmake
	@rm -f uninstall.cmake

reinstall: uninstall install

.PHONY: all configure build clean re install uninstall reinstall
