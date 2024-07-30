#include <3ds.h>

#include "ui.h"
#include "data.h"
#include "fs.h"
#include "util.h"

static ui::titleview *extView;
static bool fldOpen = false;
static ui::menu *extOpts;

static void fldCallback(void *a)
{
    switch(ui::padKeysDown())
    {
        case KEY_B:
            fs::closeSaveArch();
            fldOpen = false;
            break;
    }
}

static void extViewCallback(void *a)
{
    switch(ui::padKeysDown())
    {
        case KEY_A:
            {
                data::titleData *t = &data::extDataTitles[extView->getSelected()];
                std::string uploadParent;
                if(fs::gDrive)
                {
                    std::string ttlUTF8 = t->getTitleUTF8();
                    if(!fs::gDrive->dirExists(ttlUTF8, fs::extDataDirID))
                        fs::gDrive->createDir(ttlUTF8, fs::extDataDirID);

                    uploadParent = fs::gDrive->getFolderID(ttlUTF8, fs::extDataDirID);
                }

                if(fs::openArchive(*t, ARCHIVE_EXTDATA, false))
                {
                    util::createTitleDir(*t, ARCHIVE_EXTDATA);
                    std::u16string targetPath = util::createPath(*t, ARCHIVE_EXTDATA);
                    ui::fldInit(targetPath, uploadParent, fldCallback, NULL);
                    fldOpen = true;
                }
            }
            break;

        case KEY_CPAD_LEFT:
            ui::state = USR;
            break;

        case KEY_CPAD_RIGHT:
            ui::state = SYS;
            break;
    }
}

void ui::extInit(void *a)
{
    threadInfo *t = (threadInfo *)a;
    extView = new ui::titleview(data::extDataTitles, extViewCallback, NULL);
    extOpts = new ui::menu;

    extOpts->addOpt("删除追加数据", 320);

    t->finished = true;
}

void ui::extExit()
{
    delete extOpts;
    delete extView;
}

void ui::extUpdate()
{
    if(fldOpen)
        ui::fldUpdate();
    else
        extView->update();
}

void ui::extRefresh()
{
    extView->refesh(data::extDataTitles);
}

void ui::extDrawTop()
{
    extView->draw();
    ui::drawUIBar(TITLE_TEXT + "- 追加数据", ui::SCREEN_TOP, true);
}

void ui::extDrawBot()
{
    if(fldOpen)
    {
        ui::fldDraw();
        ui::drawUIBar(FLD_GUIDE_TEXT, ui::SCREEN_BOT, true);
    }
    else
    {
        if (!data::extDataTitles.empty())
            data::extDataTitles[extView->getSelected()].drawInfo(0, 0);
        ui::drawUIBar("\ue000 打开 \ue01A\ue077\ue019 存档类型", ui::SCREEN_BOT, false);
    }
}
