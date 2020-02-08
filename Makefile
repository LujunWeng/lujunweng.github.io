SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = source
BUILDDIR      = docs
.DEFAULT_GOAL = html

html: Makefile
	@$(SPHINXBUILD) "$(SOURCEDIR)" "$(BUILDDIR)"
