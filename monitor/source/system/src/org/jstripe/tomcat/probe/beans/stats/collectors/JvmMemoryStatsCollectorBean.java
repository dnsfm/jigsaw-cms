/*
 * Licensed under the GPL License. You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://probe.jstripe.com/d/license.shtml
 *
 *  THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
 *  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 *  WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

package org.jstripe.tomcat.probe.beans.stats.collectors;

import org.jstripe.tomcat.probe.beans.JvmMemoryInfoAccessorBean;
import org.jstripe.tomcat.probe.model.jmx.MemoryPool;

import java.util.Iterator;
import java.util.List;

public class JvmMemoryStatsCollectorBean extends BaseStatsCollectorBean {
	private JvmMemoryInfoAccessorBean jvmMemoryInfoAccessor;

	public JvmMemoryInfoAccessorBean getJvmMemoryInfoAccessor() {
		return jvmMemoryInfoAccessor;
	}

	public void setJvmMemoryInfoAccessor(
			JvmMemoryInfoAccessorBean jvmMemoryInfoAccessor) {
		this.jvmMemoryInfoAccessor = jvmMemoryInfoAccessor;
	}

	@SuppressWarnings("unchecked")
	public void collect() throws Exception {
		List pools = jvmMemoryInfoAccessor.getPools();
		long time = System.currentTimeMillis();
		for (Iterator it = pools.iterator(); it.hasNext();) {
			MemoryPool pool = (MemoryPool) it.next();
			buildAbsoluteStats("memory.pool." + pool.getName(), pool.getUsed(),
					time);
		}
	}
}
