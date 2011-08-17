/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2000 Stephan Kulow <coolo@kde.org>
                       David Faure <faure@kde.org>
 * Copyright (C) 2006 Kevin Ottens <ervin@kde.org>
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef GLUON_PLAYER_ABSTRACTJOB_H
#define GLUON_PLAYER_ABSTRACTJOB_H

#include <QtCore/QObject>
#include <QtCore/QPair>

class QVariant;

/**
 * The base class for all Gluon Player jobs.
 * For all jobs created in an application, the code looks like
 *
 * \code
 * void SomeClass::methodWithAsynchronousJobCall()
 * {
 *   AbstractJob * job = someoperation( some parameters );
 *   connect( job, SIGNAL( success() ),
 *            this, SLOT( handleSuccess() ) );
 *   job->start();
 * }
 * \endcode
 *   (other connects, specific to the job)
 *
 * @note: AbstractJob and its subclasses is meant to be used
 * in a fire-and-forget way. It's deleting itself when
 * it has finished using deleteLater() so the job
 * instance disappears after the next event loop run.
 */

class AbstractJob : public QObject
{
    Q_OBJECT

public:
    /**
     * Creates a new AbstractJob object.
     *
     * @param parent the parent QObject
     */
    explicit AbstractJob( QObject *parent = 0 );

    /**
     * Destroys a AbstractJob object.
     */
    virtual ~AbstractJob();

    /**
     * Starts the job asynchronously. When the job is finished successfully, succeeded()
     * is emitted, if the job finishes unsuccessfully, failed() is emitted. Also, in both
     * the cases finished() is also emitted.
     *
     * This method performs common initialization for the jobs and finally calls
     * startImplementation() which must be reimplemented by subclasses.
     */
    virtual void start();

    /**
     * Returns an error description string, if any. If there was no error, it returns a
     * blank string
     *
     * @return the error message
     */
    virtual QString errorText() const;

    /**
     * Returns the processed amount in bytes for this job.
     *
     * @return the processed size
     */
    qulonglong processedAmount() const;

    /**
     * Returns the total amount in bytes for this job.
     *
     * @return the total size
     */
    qulonglong totalAmount() const;

    /**
     * Returns the overall progress of this job.
     *
     * @return the overall progress of this job
     */
    unsigned long percent() const;

    /**
     * Returns whether this job automatically deletes itself once
     * the job is finished.
     *
     * @return whether the job is deleted automatically after
     * finishing.
     */
    bool isAutoDelete() const;

    /**
     * Returns the data after processing is finished.
     *
     * @return data as a QVariant which should be used as required
     */
    Q_INVOKABLE virtual QVariant data() = 0;

public Q_SLOTS:
    /**
     * Set the auto-delete property of the job. If @p autodelete is
     * set to false the job will not delete itself once it is finished.
     *
     * The default for any AbstractJob is to automatically delete itself.
     *
     * @param autodelete set to false to disable automatic deletion
     * of the job.
     */
    void setAutoDelete( bool autodelete );

    /**
     * Aborts this job.
     * This kills and deletes the job.
     *
     * @return true if the operation is supported and succeeded, false otherwise
     */
    bool kill( );

Q_SIGNALS:
    /**
     * Emitted when the job is finished, in any case. It is used to notify
     * observers that the job is terminated and that progress can be hidden.
     *
     * Use errorText to know if the job was finished with an error.
     * 
     * This signal should not be emitted directly by subclasses of
     * AbstractJob, use emitSucceeded() or emitFailed() instead.
     *
     * @see succeeded
     * @see failed
     */
    void finished();

    /**
     * Emitted when the job is finished successfully
     *
     * This signal should not be emitted directly by subclasses of
     * AbstractJob, use emitSucceeded() instead.
     *
     * @see finished
     */
    void succeeded();

    /**
     * Emitted when the job failed to perform its tasks.
     *
     * Use errorText to know what the error was.
     *
     * This signal should not be emitted directly by subclasses of
     * AbstractJob, use emitSucceeded() instead.
     *
     * @see finished
     */
    void failed();

    /**
     * Emitted to display state information about this job.
     * Examples of message are "Resolving host", "Connecting to host...", etc.
     *
     * @param job the job that emitted this signal
     * @param plain the info message
     * @param rich the rich text version of the message, or QString() is none is available
     */
    void message( const QString &plain, const QString &rich = QString() );

    /**
     * Emitted when we know the amount the job will have to process.
     *
     * This is a private signal, it can't be emitted directly by subclasses of
     * AbstractJob, use setTotalAmount() instead.
     *
     * @param amount the total amount
     */
    void totalAmount(qulonglong amount);

    /**
     * Regularly emitted to show the progress of this job by giving the current amount.
     *
     * This is a private signal, it can't be emitted directly by subclasses of
     * AbstractJob, use setProcessedAmount() instead.
     *
     * @param amount the processed amount
     */
    void processedAmount(qulonglong amount);

    /**
     * Emitted when we know the size of this job (data size in bytes for transfers,
     * number of entries for listings, etc).
     *
     * This is a private signal, it can't be emitted directly by subclasses of
     * AbstractJob, use setTotalAmount() instead.
     *
     * @param size the total size
     */
    void totalSize(qulonglong size);

    //FIXME
    /**
     * Regularly emitted to show the progress of this job
     * (current data size in bytes for transfers, entries listed, etc.).
     *
     * This is a private signal, it can't be emitted directly by subclasses of
     * AbstractJob, use setProcessedAmount() instead.
     *
     * @param size the processed size
     */
    void processedSize(qulonglong size);

    /**
     * Progress signal showing the overall progress of the job
     * This is valid for any kind of job, and allows using a
     * a progress bar very easily. (see KProgressBar).
     * Note that this signal is not emitted for finished jobs.
     *
     * This is a private signal, it can't be emitted directly by subclasses of
     * AbstractJob, use emitPercent(), setPercent() setTotalAmount() or
     * setProcessedAmount() instead.
     *
     * @param percent the percentage
     */
    void percent( unsigned long percent );

    /**
     * Emitted to display information about the speed of this job.
     *
     * This is a private signal, it can't be emitted directly by subclasses of
     * AbstractJob, use emitSpeed() instead.
     *
     * @param speed the speed in bytes/s
     */
    void speed(unsigned long speed);

protected:
    /**
     * Sets the error text.
     *
     * @param errorText the error text
     */
    void setErrorText( const QString &errorText );


    /**
     * Sets the processed size. The processedAmount() and percent() signals
     * are emitted if the values changed.
     *
     * @param amount the new processed amount
     */
    void setProcessedAmount(qulonglong amount);

    /**
     * Sets the total size. The totalSize() and percent() signals
     * are emitted if the values changed.
     *
     * @param amount the new total amount
     */
    void setTotalAmount(qulonglong amount);

    /**
     * Sets the overall progress of the job. The percent() signal
     * is emitted if the value changed.
     *
     * @param percentage the new overall progress
     */
    void setPercent( unsigned long percentage );

    /**
     * Utility function to emit the succeeded signal, and suicide this job.
     * It first notifies the observers to hide the progress for this job using
     * the finished() signal.
     *
     * @note: Deletes this job using deleteLater().
     *
     * @see finished()
     */
    void emitSucceeded();

    /**
     * Utility function to emit the failed signal, and suicide this job.
     * It first notifies the observers to hide the progress for this job using
     * the finished() signal.
     *
     * @note: Deletes this job using deleteLater().
     *
     * @see finished()
     */
    void emitFailed();

    /**
     * Utility function for inherited jobs.
     * Emits the percent signal if bigger than previous value,
     * after calculating it from the parameters.
     *
     * @param processedAmount the processed amount
     * @param totalAmount the total amount
     * @see percent()
     */
    void setPercent( qulonglong processedAmount, qulonglong totalAmount );

    /**
     * Utility function for inherited jobs.
     * Emits the speed signal and starts the timer for removing that info
     *
     * @param speed the speed in bytes/s
     */
    void emitSpeed(unsigned long speed);

    /**
     * Performs job specific operations, must be reimplemented
     * This is the method all subclasses need to implement.
     *
     * Warning: Never implement any synchronous workload in this method. This method
     * should just trigger the job startup, not do any work itself. It is expected to
     * be non-blocking.
     *
     * It should setup and trigger the workload of the job. It should not do any
     * work itself. This includes all signals and terminating the job, e.g. by
     * emitFinished(). The workload, which could be another method of the
     * subclass, is to be triggered using the event loop, e.g. by code like:
     * \code
     * void ExampleJob::startImplementation()
     * {
     *  QTimer::singleShot( 0, this, SLOT( doWork() ) );
     * }
     * \endcode
     */
    virtual void startImplementation() = 0;

    /**
     * Aborts this job and emit finished() signal
     *
     * @return true if the operation is supported and succeeded, false otherwise
     */
    virtual bool doKill();

private:
    class Private;
    Private* const d;

    Q_PRIVATE_SLOT( d, void _k_speedTimeout() )
};

#endif // GLUONPLAYER_ABSTRACTJOB_H
