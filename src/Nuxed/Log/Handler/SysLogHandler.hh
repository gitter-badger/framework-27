<?hh // strict

namespace Nuxed\Log\Handler;

use namespace HH\Lib\Str;
use namespace Nuxed\Log\Exception;
use type Nuxed\Log\record;
use type Nuxed\Contract\Log\LogLevel;
use function closelog;
use function openlog;
use function syslog;
use const LOG_PID;
use const LOG_DEBUG;
use const LOG_INFO;
use const LOG_NOTICE;
use const LOG_WARNING;
use const LOG_ERR;
use const LOG_CRIT;
use const LOG_ALERT;
use const LOG_EMERG;

class SysLogHandler extends AbstractHandler {
  /**
   * Translates Monolog log levels to syslog log priorities.
   */
  protected dict<LogLevel, int> $logLevels = dict[
    LogLevel::DEBUG => LOG_DEBUG,
    LogLevel::INFO => LOG_INFO,
    LogLevel::NOTICE => LOG_NOTICE,
    LogLevel::WARNING => LOG_WARNING,
    LogLevel::ERROR => LOG_ERR,
    LogLevel::CRITICAL => LOG_CRIT,
    LogLevel::ALERT => LOG_ALERT,
    LogLevel::EMERGENCY => LOG_EMERG,
  ];

  /**
   * @param LogLevel   $level  The minimum logging level at which this handler will be triggered
   * @param bool       $bubble Whether the messages that are handled can bubble up the stack or not
   */
  public function __construct(
    protected string $ident,
    protected SysLogFacility $facility = SysLogFacility::USER,
    LogLevel $level = LogLevel::DEBUG,
    bool $bubble = true,
    protected int $options = LOG_PID,
  ) {
    parent::__construct($level, $bubble);
  }

  <<__Override>>
  public function write(record $record): void {
    if (!openlog($this->ident, $this->options, (int)$this->facility)) {
      throw new Exception\LogicException(Str\format(
        "Can't open syslog for ident %s and facility %d",
        $this->ident,
        (int)$this->facility,
      ));
    }

    syslog(
      $this->logLevels[$record['level']],
      $record['formatted'] ?? $record['message'],
    );
  }

  <<__Override>>
  public function close(): void {
    closelog();
  }
}
