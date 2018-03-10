/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "Config.h"

Config* Config::instance()
{
    static Config instance;
    return &instance;
}

ToolTypes Config::selectedTool() const
{
    return mConfig.value(QStringLiteral("Application/SelectedTool"), static_cast<int>(ToolTypes::Arrow)).value<ToolTypes>();
}

void Config::setSelectedTool(ToolTypes tool)
{
    if(selectedTool() == tool) {
        return;
    }

    mConfig.setValue(QStringLiteral("Application/SelectedTool"), static_cast<int>(tool));
    mConfig.sync();
}

QColor Config::toolColor(ToolTypes tool) const
{
    return mConfig.value(ConfigNameFormatter::toolColorString(tool), QColor(Qt::red)).value<QColor>();
}

void Config::setToolColor(const QColor& color, ToolTypes tool)
{
    if(toolColor(tool) == color) {
        return;
    }

    mConfig.setValue(ConfigNameFormatter::toolColorString(tool), color);
    mConfig.sync();
}

int Config::toolSize(ToolTypes tool) const
{
    return mConfig.value(ConfigNameFormatter::toolSizeString(tool), 3).value<int>();
}

void Config::setToolSize(int size, ToolTypes tool)
{
    if(toolSize(tool) == size) {
        return;
    }

    mConfig.setValue(ConfigNameFormatter::toolSizeString(tool), size);
    mConfig.sync();
}

FillTypes Config::toolFillType(ToolTypes tool) const
{
    return mConfig.value(ConfigNameFormatter::toolFillTypeString(tool), static_cast<int>(FillTypes::SameFill)).value<FillTypes>();
}

void Config::setToolFillType(FillTypes fillType, ToolTypes tool)
{
    if(toolFillType(tool) == fillType) {
        return;
    }

    mConfig.setValue(ConfigNameFormatter::toolFillTypeString(tool), static_cast<int>(fillType));
    mConfig.sync();
}

// Private Methodes

Config::Config()
{
    // You must set the application name via QCoreApplication::setApplicationName before using the configuration
    if(mConfig.status() == QSettings::AccessError) {
        qCritical("Configuration error! Are you trying to read configuration before settings Application Name?");
    }
};