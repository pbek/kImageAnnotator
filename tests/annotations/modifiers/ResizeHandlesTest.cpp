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

#include "ResizeHandlesTest.h"

void ResizeHandlesTest::TestInitHandles_Should_PositionTwoHandles_When_LineItemProvided()
{
    AnnotationProperties properties(Qt::red, 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    ResizeHandles resizeHandles(5);

    resizeHandles.initHandles(&lineItem);

    QCOMPARE(resizeHandles.handles().count(), 2);
    QCOMPARE(resizeHandles.handles()[0].center(), p1);
    QCOMPARE(resizeHandles.handles()[1].center(), p2);
}

void ResizeHandlesTest::TestInitHandles_Should_PositionEightHandles_When_RectItemProvided()
{
    AnnotationProperties properties(Qt::red, 2);
    QRectF rect(QPointF(10, 15), QPointF(20, 25));
    AnnotationRect rectItem(rect.topLeft(), properties);
    rectItem.addPoint(rect.bottomRight());
    ResizeHandles resizeHandles(5);

    resizeHandles.initHandles(&rectItem);

    QCOMPARE(resizeHandles.handles().count(), 8);
    QCOMPARE(resizeHandles.handles()[0].center(), rect.topLeft());
    QCOMPARE(resizeHandles.handles()[1].center(), QPointF(rect.center().x(), rect.top()));
    QCOMPARE(resizeHandles.handles()[2].center(), rect.topRight());
    QCOMPARE(resizeHandles.handles()[3].center(), QPointF(rect.right(), rect.center().y()));
    QCOMPARE(resizeHandles.handles()[4].center(), rect.bottomRight());
    QCOMPARE(resizeHandles.handles()[5].center(), QPointF(rect.center().x(), rect.bottom()));
    QCOMPARE(resizeHandles.handles()[6].center(), rect.bottomLeft());
    QCOMPARE(resizeHandles.handles()[7].center(), QPointF(rect.left(), rect.center().y()));
}

void ResizeHandlesTest::TestIndexOfHandleAt_Should_ReturnIndexOfHandle_When_HandleIsAtProvidedPosition()
{
    AnnotationProperties properties(Qt::red, 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    ResizeHandles resizeHandles(5);
    resizeHandles.initHandles(&lineItem);

    auto resultP1 = resizeHandles.indexOfHandleAt(p1 + QPointF(2, 2));
    auto resultP2 = resizeHandles.indexOfHandleAt(p2 + QPointF(-2, -2));

    QCOMPARE(resizeHandles.handles().count(), 2);
    QCOMPARE(resultP1, 0);
    QCOMPARE(resultP2, 1);
}

void ResizeHandlesTest::TestIndexOfHandleAt_Should_NotReturnAnyIndex_When_HandleIsNotAtProvidedPosition()
{
    AnnotationProperties properties(Qt::red, 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    ResizeHandles resizeHandles(5);
    resizeHandles.initHandles(&lineItem);

    auto resultP1 = resizeHandles.indexOfHandleAt(QPointF(50, 50));

    QCOMPARE(resizeHandles.handles().count(), 2);
    QCOMPARE(resultP1, -1);
}

void ResizeHandlesTest::TestHandle_Should_ReturnRectAtIndex_When_HandleAtIndexExists()
{
    AnnotationProperties properties(Qt::red, 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    ResizeHandles resizeHandles(5);
    resizeHandles.initHandles(&lineItem);

    auto result = resizeHandles.handle(1);

    QVERIFY(result != QRectF());
    QCOMPARE(result.center(), p2);
}

void ResizeHandlesTest::TestHandle_Should_NotReturnRect_When_HandleAtIndexDoesntExists()
{
    AnnotationProperties properties(Qt::red, 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    ResizeHandles resizeHandles(5);
    resizeHandles.initHandles(&lineItem);

    auto result = resizeHandles.handle(3);

    QCOMPARE(result, QRectF());
}

void ResizeHandlesTest::TestGetCursorForHandle_Should_NotReturnDefaultCursor_When_ProvidedPositionOnHandle()
{
    AnnotationProperties properties(Qt::red, 1);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    ResizeHandles resizeHandles(5);
    resizeHandles.initHandles(&lineItem);

    auto result = resizeHandles.cursorForPos(p1);

    QVERIFY(result != CursorHelper::defaultCursor());
}

void ResizeHandlesTest::TestGetCursorForHandle_Should_ReturnDefaultCursor_When_ProvidedPositionNotOnHandle()
{
    AnnotationProperties properties(Qt::red, 1);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    QPointF p3(50, 50);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    ResizeHandles resizeHandles(5);
    resizeHandles.initHandles(&lineItem);

    auto result = resizeHandles.cursorForPos(p3);

    QCOMPARE(result, CursorHelper::defaultCursor());
}

QTEST_MAIN(ResizeHandlesTest);