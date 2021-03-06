<?php
/**
 * @file
 * FacebookInstantArticlesSimpleXMLElement.inc.
 */

/**
 * Extension for SimpleXMLElement.
 */
class FacebookInstantArticlesSimpleXMLElement extends SimpleXMLElement {
  /**
   * Add CDATA text in a node.
   *
   * @param string $cdata_text
   *    The CDATA value to add.
   */
  private function addCdata($cdata_text) {
    $node = dom_import_simplexml($this);
    if (($no = $node->ownerDocument) && is_string($cdata_text)) {
      $node->appendChild($no->createCDATASection($cdata_text));
    }
  }

  /**
   * Create a child with CDATA value.
   *
   * @param string $name
   *    The name of the child element to add.
   * @param string $cdata_text
   *    The CDATA value of the child element.
   *
   * @return object
   *   The child element.
   */
  public function addChildCdata($name, $cdata_text) {
    $child = $this->addChild($name);
    $child->addCdata($cdata_text);
    return $child;
  }

  /**
   * Add SimpleXMLElement code into a SimpleXMLElement.
   *
   * @param SimpleXMLElement $append
   *    XMLElement to append to.
   */
  public function appendXml(SimpleXMLElement $append) {
    if ($append) {
      if (strlen(trim((string) $append)) == 0) {
        $xml = $this->addChild($append->getName());
        foreach ($append->children() as $child) {
          $xml->appendXml($child);
        }
      }
      else {
        $xml = $this->addChild($append->getName(), (string) $append);
      }
      foreach ($append->attributes() as $n => $v) {
        $xml->addAttribute($n, $v);
      }
    }
  }

}
