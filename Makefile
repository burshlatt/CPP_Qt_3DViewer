CC = g++
FLAGS = -Wall -Wextra -Werror -std=c++17

#	== ВЫПОЛНИТЬ ВСЕ ДЕЙСТВИЯ ==
.PHONY: all
all: clean uninstall dist install

#	== УСТАНОВКА ПРОГРАММЫ ==
.PHONY: install
install:
	@echo -------------------- INSTALL --------------------
	make uninstall --quiet
	mkdir build
	cp Makefile build && qmake && make && make clean && rm -rf Makefile .qmake.stash && mv build/Makefile . && mv 3DViewer.app build
	@echo -------------------- SUCCESS --------------------

#	== ЗАПУСК ПРОГРАММЫ ==
.PHONY: open
open:
	@echo --------------------- OPEN ----------------------
	cd build && open 3DViewer.app
	@echo -------------------- SUCCESS --------------------
	
#	== УДАЛЕНИЕ ПРОГРАММЫ ==
.PHONY: uninstall
uninstall:
	@echo ------------------- UNINSTALL -------------------
	rm -rf build
	@echo -------------------- SUCCESS --------------------

#	== ОЧИСТКА ФАЙЛОВ ==
.PHONY: clean
clean:
	@echo --------------------- START ---------------------
	rm -rf 3DViewer.tar.gz
	@echo -------------------- SUCCESS --------------------

#	== СОЗДАНИЕ АРХИВА ПРОЕКТА ==
.PHONY: dist
dist: clean uninstall
	@echo --------------------- START ---------------------
	tar czvf 3DViewer.tar.gz .
	@echo -------------------- SUCCESS --------------------

#	== ПРОВЕРКА СТИЛЯ ==
.PHONY: style
style:
	@echo --------------------- STYLE ---------------------
	clang-format -n -style=GOOGLE *.cc */*.cc */*/*.cc */*.h */*/*.h
	@echo -------------------- SUCCESS --------------------

