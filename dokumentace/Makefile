main.pdf: main.tex obsah.tex
	lualatex main.tex
	lualatex main.tex

obsah.tex: obsah.md
	pandoc --top-level-division=chapter -o obsah.tex obsah.md
