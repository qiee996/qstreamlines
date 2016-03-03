#ifndef EXPORTER_H
#define EXPORTER_H

#include <QString>

namespace qst {

class Exporter
{
public:
    Exporter();

    void setEnabled(bool enable);
    void setOutputPath(const QString & str);
    virtual void write(int frameid) = 0;

protected:
    bool mEnabled;
    QString mOutputPath;
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