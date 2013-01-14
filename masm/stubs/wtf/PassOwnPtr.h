/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the V4VM module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef PASSOWNPTR_H
#define PASSOWNPTR_H

#include <qscopedpointer.h>

template <typename T> class PassOwnPtr;
template <typename PtrType> PassOwnPtr<PtrType> adoptPtr(PtrType*);

template <typename T>
struct OwnPtr : public QScopedPointer<T>
{
    OwnPtr() {}
    OwnPtr(const PassOwnPtr<T> &ptr)
        : QScopedPointer<T>(ptr.leakRef())
    {}

    OwnPtr& operator=(const OwnPtr<T>& other)
    {
        this->reset(const_cast<OwnPtr<T> &>(other).take());
        return *this;
    }

    T* get() const { return this->data(); }

    PassOwnPtr<T> release()
    {
        return adoptPtr(this->take());
    }
};

template <typename T>
class PassOwnPtr {
public:
    PassOwnPtr() {}

    PassOwnPtr(T* ptr)
        : m_ptr(ptr)
    {
    }

    PassOwnPtr(const PassOwnPtr<T>& other)
        : m_ptr(other.leakRef())
    {
    }

    PassOwnPtr(const OwnPtr<T>& other)
        : m_ptr(other.take())
    {
    }

    ~PassOwnPtr()
    {
    }

    T* operator->() const { return m_ptr.data(); }

    T* leakRef() const { return m_ptr.take(); }

private:
    template <typename PtrType> friend PassOwnPtr<PtrType> adoptPtr(PtrType*);

    PassOwnPtr<T>& operator=(const PassOwnPtr<T>&)
    {}
    mutable QScopedPointer<T> m_ptr;
};

template <typename T>
PassOwnPtr<T> adoptPtr(T* ptr)
{
    PassOwnPtr<T> result;
    result.m_ptr.reset(ptr);
    return result;
}


#endif // PASSOWNPTR_H
