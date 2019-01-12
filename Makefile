# Requires the following project directory structure:
#  /bin
#  /obj
#  /src

# Use 'make remove' to clean up the hole project

# Name of target file
TARGET     = crawly

CC        = clang
CCFLAGS   = -std=c17 \
             -g -Weverything -Wall -Wextra -pedantic-errors \
             -O3 -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition \
             -D_XOPEN_SOURCE=700

LD         = clang -o
LDFLAGS    = -Wall -pedantic

SRCDIR     = src
OBJDIR     = obj
BINDIR     = bin
DEPDIR     = dep

# # flags required for dependency generation; passed to compilers
DEPFLAGS = -MT $@ -MD -MP -MF $(DEPDIR)/$*.d

SOURCES   := \
             src/main.c \
             src/cJSON.c

INCLUDES  := $(wildcard $(SRCDIR)/*.h)
OBJECTS   := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPENDS   := $(SOURCES:$(SRCDIR)/%.c=$(DEPDIR)/%.d)
RM         = rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LD) $@ $(LDFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CCFLAGS) $(DEPFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"


.PHONY: clean
clean: 
	@$(RM) $(OBJECTS) $(DEPENDS)
	@$(RM) $(BINDIR)/$(TARGET)
	@echo "Cleanup completed!"

print-%  : ; @echo $* = $($*)