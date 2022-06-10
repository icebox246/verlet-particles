SOURCES = 
SOURCES += src/main.c
SOURCES += src/la.c
SOURCES += src/body.c
SOURCES += src/line.c
SOURCES += src/state.c

FLAGS = $(shell pkg-config sdl2 --cflags --libs)
FLAGS += -lm

EFLAGS = -s USE_SDL=2
EFLAGS += --shell-file src/template.html

main: ${SOURCES}
	gcc ${FLAGS} ${SOURCES} -o out


web: ${SOURCES} src/template.html
	emcc ${SOURCES} ${EFLAGS} -o web/index.html 
