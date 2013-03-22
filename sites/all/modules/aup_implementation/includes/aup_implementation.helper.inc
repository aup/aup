<?php 

class NodequeueQueues {
	
	protected $queues;
	
	public function __construct() {
		
		$query = db_query("select * from {nodequeue_queue} order by title asc;");
		$queues[0] = '<none>';
		
		foreach($query as $row)
			$queues[$row->qid] = $row->title;
		
		$this->queues = $queues;
		
	}
	
	public function getQueues() {
		
		return $this->queues;
		
	}
	
	
	
}

class NodequeueNodes {
	
	protected $nodes;
	protected $queue_title;
	
	public function __construct($qid) {
		
		$result = db_query('SELECT DISTINCT nq.title as nodequeue_title, n.* FROM {node} n INNER JOIN {nodequeue_nodes} nqn ON nqn.nid = n.nid INNER JOIN {nodequeue_queue} nq ON nq.qid = nqn.qid WHERE nqn.sqid = :qid ORDER BY nqn.position ASC', array(':qid' => $qid));
		$nodes = array();
		
		foreach($result as $row)			
			$nodes[] = node_load($row->nid);
		
		if(!empty($row)) {
			$this->queue_title = $row->nodequeue_title;
			$this->nodes = $nodes;
		} else {
			$this->queue_title = '';
			$this->nodes = null;
		}
		
	}
	
	public function getNodes() {
		
		if (sizeof($this->nodes) > 0)
			return $this->nodes;
		
	}
	
	public function getQueueTitle() {
		
		return $this->queue_title;
		
	}
	
	public function getRandomNode() {
		
		if (sizeof($this->nodes) > 0)
			return $this->nodes[array_rand($this->nodes, 1)];
		
	}
	
	public static function getFullNodequeueReference($random, $nodes) {
		
		$items = array();
		
		$items['random'] = (object) $random;
		$items['nodes'] = (array) $nodes;
		
		return $items;
		
	}
	
}