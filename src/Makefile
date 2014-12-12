OUT         := irc_bot
SRC         := main.cpp IRCBot.cpp ConfigManager.cpp PluginManager.cpp
OBJ         := $(patsubst %.c, %.o, $(filter %.c, $(SRC)))
OBJ         += $(patsubst %.cpp, %.o, $(filter %.cpp, $(SRC)))
DEP         := $(OBJ:.o=.d)

CFLAGS      := -Wall -Werror -pedantic -std=c99
CXXFLAGS    := -Wall -Werror -pedantic -std=c++11
LDFLAGS     :=
LDLIBS      := -ldl

DEBUG       ?= 0
VERBOSE     ?= 0

ifeq ($(DEBUG),1)
	CFLAGS += -O0 -g3 -ggdb -pg
	CXXFLAGS += -O0 -g3 -ggdb -pg
endif

ifeq ($(VERBOSE),1)
	MSG := @true
	CMD :=
else
	MSG := @echo
	CMD := @
endif

ifeq ($(origin PKG_CONFIG), undefined)
  PKG_CONFIG = pkg-config
  ifeq ($(shell which $(PKG_CONFIG) 2>/dev/null),)
    $(error $(PKG_CONFIG) not found)
  endif
endif

ifeq ($(origin LIBCONFIGPP_CFLAGS) $(origin LIBCONFIGPP_LDLIBS),undefined undefined)
  ifeq ($(shell $(PKG_CONFIG) --modversion libconfig++ 2>/dev/null),)
    $(error libconfig++ development libraries not found)
  endif
  LIBCONFIGPP_CFLAGS += $(shell $(PKG_CONFIG) --cflags libconfig++)
  LIBCONFIGPP_LDLIBS += $(shell $(PKG_CONFIG) --libs libconfig++)
endif
CFLAGS += $(LIBCONFIGPP_CFLAGS)
CXXFLAGS += $(LIBCONFIGPP_CFLAGS)
LDLIBS += $(LIBCONFIGPP_LDLIBS)

USE_SFML_SOCKETS ?= 1

ifeq ($(USE_SFML_SOCKETS),1)
    ifeq ($(origin SFMLNETWORK_CFLAGS) $(origin SFMLNETWORK_LDLIBS),undefined undefined)
      ifeq ($(shell $(PKG_CONFIG) --modversion sfml-network 2>/dev/null),)
        $(error SFML network development libraries not found)
      endif
      SFMLNETWORK_CFLAGS += $(shell $(PKG_CONFIG) --cflags sfml-network)
      SFMLNETWORK_LDLIBS += $(shell $(PKG_CONFIG) --libs sfml-network)
    endif
    CFLAGS += -DUSE_SFML_SOCKETS $(SFMLNETWORK_CFLAGS)
    CXXFLAGS += -DUSE_SFML_SOCKETS $(SFMLNETWORK_CFLAGS)
    LDLIBS += $(SFMLNETWORK_LDLIBS)
endif

.PHONY: release clean

release: CFLAGS += -O2
release: CXXFLAGS += -O2
release: $(OUT)

clean:
	$(MSG) -e "\tCLEAN\t"
	$(CMD)$(RM) $(OBJ) $(DEP) $(OUT)

$(OUT): $(OBJ)
	$(MSG) -e "\tLINK\t$@"
	$(CMD)$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c %.d
	$(MSG) -e "\tCC\t$@"
	$(CMD)$(CC) $(CFLAGS) -c $< -o $@

%.d: %.c
	$(MSG) -e "\tDEP\t$@"
	$(CMD)$(CC) $(CFLAGS) -MF $@ -MM $<

%.o: %.cpp %.d
	$(MSG) -e "\tCXX\t$@"
	$(CMD)$(CXX) $(CXXFLAGS) -c $< -o $@

%.d: %.cpp
	$(MSG) -e "\tDEP\t$@"
	$(CMD)$(CXX) $(CXXFLAGS) -MF $@ -MM $<

ifneq ($(MAKECMDGOALS),clean)
-include $(DEP)
endif

