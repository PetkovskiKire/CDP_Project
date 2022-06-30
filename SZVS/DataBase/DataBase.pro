TYPE = application
PROJECTNAME = DataBase

DEPS += szvslib testbaza

HEADERS += Libraries.h
SOURCES += CDPMain.cpp

DISTFILES += \
    $$files(*.xml, true) \
    $$files(*.lic, true) \
    $$files(Application/www/*.*, true) \
    Application/index.html \
    Application/www/vue/bytebuffer.min.js \
    Application/www/vue/images/cdpstudio.png \
    Application/www/vue/index.html \
    Application/www/vue/jquery.min.js \
    Application/www/vue/jquery.slim.min.map \
    Application/www/vue/long.min.js \
    Application/www/vue/model.js \
    Application/www/vue/protobuf.min.js \
    Application/www/vue/semantic.min.css \
    Application/www/vue/semantic.min.js \
    Application/www/vue/studioapi.js \
    Application/www/vue/studioapi.proto \
    Application/www/vue/themes/basic/assets/fonts/icons.svg \
    Application/www/vue/themes/basic/assets/fonts/icons.ttf \
    Application/www/vue/themes/default/assets/fonts/icons.svg \
    Application/www/vue/themes/default/assets/fonts/icons.ttf \
    Application/www/vue/themes/default/assets/fonts/icons.woff \
    Application/www/vue/themes/default/assets/fonts/icons.woff2 \
    Application/www/vue/vue.app-card.js \
    Application/www/vue/vue.common.min.js \
    Application/www/vue/vue.common.min.js.map \
    Application/www/vue/vue.component-card.js \
    Application/www/vue/vue.expand.js \
    Application/www/vue/vue.min.js

load(cdp)

ID = 390140464415578 # do not change
