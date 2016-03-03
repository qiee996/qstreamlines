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
/*
    LICENSE BEGIN

    qstreamlines - Realtime streamlines animator.
    Copyright (C) 2016  Remik Ziemlinski

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    LICENSE END
*/