////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Поток для загрузки Qt ресурсов.
         \en Stream for loading Qt resources. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __QT_RESSTREAM_H
#define __QT_RESSTREAM_H

#include <QResource>
#include <vsn_resourcestream.h>

VSN_BEGIN_NAMESPACE

/** \brief \ru ВНИМАНИЕ! Этот файл не является частью API Vision. Он необходим для иллюстрации использования
               ядра Vision с библиотекой Qt и ее классами. Этот заголовочный файл может изменяться от версии
               к версии без предупреждения или полностью удаляться.
           \en WARNING! The file is not a part of API Vision. It is needed to illustrate using of the Vision kernel
               with Qt library and its classes. This header file can be changed from version to version with
               no warning or completely deleted. \~
*/

namespace QtVision {
//------------------------------------------------------------------------------
/** \brief \ru Класс QtResStream служит для загрузки Qt ресурсов.
           \en Class QtResStream is needed to load Qt resources. \~
    \ingroup Vision_OpenGL
*/
// ---
class QtResStream : public ResourceStream
{
public:
    QtResStream(const QString & res)
        : ResourceStream()
        , m_resource(res)
    {
        if (m_resource.isCompressed())
        {
            m_pUncompressData = qUncompress(m_resource.data(), m_resource.size());
            size_t length = m_pUncompressData.size();
            Init(m_pUncompressData.data(), length);
        }
        else
        {
            size_t length = m_resource.size();
            Init(m_resource.data(), length);
        }


    }

private:
    QResource  m_resource;
    QByteArray m_pUncompressData;
};

} // namespace QtVision

VSN_END_NAMESPACE

#endif //__QT_RESSTREAM_H

