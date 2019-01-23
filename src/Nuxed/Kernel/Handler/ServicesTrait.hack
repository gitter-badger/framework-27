namespace Nuxed\Kernel\Handler;

use type Nuxed\Contract\Container\ContainerAwareInterface;
use type Nuxed\Container\ContainerAwareTrait;
use namespace Nuxed\Contract\Log;
use namespace Nuxed\Contract\Http;
use namespace Nuxed\Contract\Cache;
use namespace Nuxed\Contract\Crypto;
use namespace Nuxed\Contract\Http\Router;
use type AsyncMysqlConnection;
use type SQLite3;

trait ServicesTrait implements ContainerAwareInterface {
  require implements Http\Server\RequestHandlerInterface;
  use ContainerAwareTrait;

  protected function getService<T>(classname<T> $service): T {
    // UNSAFE
    return $this->getContainer()->get($service);
  }


  protected function logger(): Log\LoggerInterface {
    return $this->getService(Log\LoggerInterface::class);
  }

  protected function cache(): Cache\CacheInterface {
    return $this->getService(Cache\CacheInterface::class);
  }

  protected function mysql(): AsyncMysqlConnection {
    return $this->getService(AsyncMysqlConnection::class);
  }

  protected function sqlite(): SQLite3 {
    return $this->getService(SQLite3::class);
  }
  protected function crypto(): Crypto\CryptoInterface {
    return $this->getService(Crypto\CryptoInterface::class);
  }

  protected function router(): Router\RouterInterface {
    return $this->getService(Router\RouterInterface::class);
  }
}
