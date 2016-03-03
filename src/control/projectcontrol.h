#ifndef PROJECTCONTROL_H
#define PROJECTCONTROL_H

#include "model/cli.h"
#include "model/project.h"
#include "view/propertieswidget.h"

namespace qst {

class ProjectControl
{
public:
    void setCli(Cli *cli);
    void setProject(Project *p);
    void updateUi(PropertiesWidget *ui);

private:
    Project *mProject;
};

}
#endif
