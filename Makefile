SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = .
BUILDDIR      = docs
.DEFAULT_GOAL = html

html: Makefile
	@$(SPHINXBUILD) "$(SOURCEDIR)" "$(BUILDDIR)"

all: html
	git add -A && git commit -v
	git push
