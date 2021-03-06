/*
 * Copyright (c) 2012 Jiri Svoboda
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/** @addtogroup libc
 * @{
 */
/**
 * @file
 * @brief IP link server stub
 */

#include <errno.h>
#include <ipc/iplink.h>
#include <stdlib.h>
#include <sys/types.h>
#include <inet/addr.h>
#include <inet/iplink_srv.h>

static void iplink_get_mtu_srv(iplink_srv_t *srv, ipc_callid_t callid,
    ipc_call_t *call)
{
	size_t mtu;
	int rc = srv->ops->get_mtu(srv, &mtu);
	async_answer_1(callid, rc, mtu);
}

static void iplink_get_mac48_srv(iplink_srv_t *srv, ipc_callid_t iid,
    ipc_call_t *icall)
{
	addr48_t mac;
	int rc = srv->ops->get_mac48(srv, &mac);
	if (rc != EOK) {
		async_answer_0(iid, rc);
		return;
	}
	
	ipc_callid_t callid;
	size_t size;
	if (!async_data_read_receive(&callid, &size)) {
		async_answer_0(callid, EREFUSED);
		async_answer_0(iid, EREFUSED);
		return;
	}
	
	if (size != sizeof(addr48_t)) {
		async_answer_0(callid, EINVAL);
		async_answer_0(iid, EINVAL);
		return;
	}
	
	rc = async_data_read_finalize(callid, &mac, size);
	if (rc != EOK)
		async_answer_0(callid, rc);
	
	async_answer_0(iid, (sysarg_t) rc);
}

static void iplink_set_mac48_srv(iplink_srv_t *srv, ipc_callid_t iid,
    ipc_call_t *icall)
{
	int rc;
	size_t size;
	addr48_t mac;
	ipc_callid_t callid;

	rc = async_data_write_receive(&callid, &size);
	if (rc != EOK) {
		async_answer_0(callid, (sysarg_t) rc);
		async_answer_0(iid, (sysarg_t) rc);
	}

	rc = srv->ops->set_mac48(srv, &mac);
	if (rc != EOK) {
		async_answer_0(iid, rc);
		return;
	}
	
	rc = async_data_read_finalize(callid, &mac, sizeof(addr48_t));
	if (rc != EOK)
		async_answer_0(callid, rc);
	
	async_answer_0(iid, (sysarg_t) rc);
}

static void iplink_addr_add_srv(iplink_srv_t *srv, ipc_callid_t iid,
    ipc_call_t *icall)
{
	ipc_callid_t callid;
	size_t size;
	if (!async_data_write_receive(&callid, &size)) {
		async_answer_0(callid, EREFUSED);
		async_answer_0(iid, EREFUSED);
		return;
	}
	
	if (size != sizeof(inet_addr_t)) {
		async_answer_0(callid, EINVAL);
		async_answer_0(iid, EINVAL);
		return;
	}
	
	inet_addr_t addr;
	int rc = async_data_write_finalize(callid, &addr, size);
	if (rc != EOK) {
		async_answer_0(callid, (sysarg_t) rc);
		async_answer_0(iid, (sysarg_t) rc);
	}
	
	rc = srv->ops->addr_add(srv, &addr);
	async_answer_0(iid, (sysarg_t) rc);
}

static void iplink_addr_remove_srv(iplink_srv_t *srv, ipc_callid_t iid,
    ipc_call_t *icall)
{
	ipc_callid_t callid;
	size_t size;
	if (!async_data_write_receive(&callid, &size)) {
		async_answer_0(callid, EREFUSED);
		async_answer_0(iid, EREFUSED);
		return;
	}
	
	if (size != sizeof(inet_addr_t)) {
		async_answer_0(callid, EINVAL);
		async_answer_0(iid, EINVAL);
		return;
	}
	
	inet_addr_t addr;
	int rc = async_data_write_finalize(callid, &addr, size);
	if (rc != EOK) {
		async_answer_0(callid, (sysarg_t) rc);
		async_answer_0(iid, (sysarg_t) rc);
	}
	
	rc = srv->ops->addr_remove(srv, &addr);
	async_answer_0(iid, (sysarg_t) rc);
}

static void iplink_send_srv(iplink_srv_t *srv, ipc_callid_t iid,
    ipc_call_t *icall)
{
	iplink_sdu_t sdu;
	
	sdu.src = IPC_GET_ARG1(*icall);
	sdu.dest = IPC_GET_ARG2(*icall);
	
	int rc = async_data_write_accept(&sdu.data, false, 0, 0, 0,
	    &sdu.size);
	if (rc != EOK) {
		async_answer_0(iid, rc);
		return;
	}
	
	rc = srv->ops->send(srv, &sdu);
	free(sdu.data);
	async_answer_0(iid, rc);
}

static void iplink_send6_srv(iplink_srv_t *srv, ipc_callid_t iid,
    ipc_call_t *icall)
{
	iplink_sdu6_t sdu;
	
	ipc_callid_t callid;
	size_t size;
	if (!async_data_write_receive(&callid, &size)) {
		async_answer_0(callid, EREFUSED);
		async_answer_0(iid, EREFUSED);
		return;
	}
	
	if (size != sizeof(addr48_t)) {
		async_answer_0(callid, EINVAL);
		async_answer_0(iid, EINVAL);
		return;
	}
	
	int rc = async_data_write_finalize(callid, &sdu.dest, size);
	if (rc != EOK) {
		async_answer_0(callid, (sysarg_t) rc);
		async_answer_0(iid, (sysarg_t) rc);
	}
	
	rc = async_data_write_accept(&sdu.data, false, 0, 0, 0,
	    &sdu.size);
	if (rc != EOK) {
		async_answer_0(iid, rc);
		return;
	}
	
	rc = srv->ops->send6(srv, &sdu);
	free(sdu.data);
	async_answer_0(iid, rc);
}

void iplink_srv_init(iplink_srv_t *srv)
{
	fibril_mutex_initialize(&srv->lock);
	srv->connected = false;
	srv->ops = NULL;
	srv->arg = NULL;
	srv->client_sess = NULL;
}

int iplink_conn(ipc_callid_t iid, ipc_call_t *icall, void *arg)
{
	iplink_srv_t *srv = (iplink_srv_t *) arg;
	int rc;
	
	fibril_mutex_lock(&srv->lock);
	if (srv->connected) {
		fibril_mutex_unlock(&srv->lock);
		async_answer_0(iid, EBUSY);
		return EBUSY;
	}
	
	srv->connected = true;
	fibril_mutex_unlock(&srv->lock);
	
	/* Accept the connection */
	async_answer_0(iid, EOK);
	
	async_sess_t *sess = async_callback_receive(EXCHANGE_SERIALIZE);
	if (sess == NULL)
		return ENOMEM;
	
	srv->client_sess = sess;
	
	rc = srv->ops->open(srv);
	if (rc != EOK)
		return rc;
	
	while (true) {
		ipc_call_t call;
		ipc_callid_t callid = async_get_call(&call);
		sysarg_t method = IPC_GET_IMETHOD(call);
		
		if (!method) {
			/* The other side has hung up */
			fibril_mutex_lock(&srv->lock);
			srv->connected = false;
			fibril_mutex_unlock(&srv->lock);
			async_answer_0(callid, EOK);
			break;
		}
		
		switch (method) {
		case IPLINK_GET_MTU:
			iplink_get_mtu_srv(srv, callid, &call);
			break;
		case IPLINK_GET_MAC48:
			iplink_get_mac48_srv(srv, callid, &call);
			break;
		case IPLINK_SET_MAC48:
			iplink_set_mac48_srv(srv, callid, &call);
			break;
		case IPLINK_SEND:
			iplink_send_srv(srv, callid, &call);
			break;
		case IPLINK_SEND6:
			iplink_send6_srv(srv, callid, &call);
			break;
		case IPLINK_ADDR_ADD:
			iplink_addr_add_srv(srv, callid, &call);
			break;
		case IPLINK_ADDR_REMOVE:
			iplink_addr_remove_srv(srv, callid, &call);
			break;
		default:
			async_answer_0(callid, EINVAL);
		}
	}
	
	return srv->ops->close(srv);
}

/* XXX Version should be part of @a sdu */
int iplink_ev_recv(iplink_srv_t *srv, iplink_recv_sdu_t *sdu, ip_ver_t ver)
{
	if (srv->client_sess == NULL)
		return EIO;
	
	async_exch_t *exch = async_exchange_begin(srv->client_sess);
	
	ipc_call_t answer;
	aid_t req = async_send_1(exch, IPLINK_EV_RECV, (sysarg_t)ver,
	    &answer);
	
	int rc = async_data_write_start(exch, sdu->data, sdu->size);
	async_exchange_end(exch);
	
	if (rc != EOK) {
		async_forget(req);
		return rc;
	}
	
	sysarg_t retval;
	async_wait_for(req, &retval);
	if (retval != EOK)
		return retval;
	
	return EOK;
}

int iplink_ev_change_addr(iplink_srv_t *srv, addr48_t *addr)
{
	if (srv->client_sess == NULL)
		return EIO;
	
	async_exch_t *exch = async_exchange_begin(srv->client_sess);
	
	ipc_call_t answer;
	aid_t req = async_send_0(exch, IPLINK_EV_CHANGE_ADDR, &answer);
	
	int rc = async_data_write_start(exch, addr, sizeof(addr48_t));
	async_exchange_end(exch);
	
	if (rc != EOK) {
		async_forget(req);
		return rc;
	}
	
	sysarg_t retval;
	async_wait_for(req, &retval);
	if (retval != EOK)
		return retval;
	
	return EOK;
}

/** @}
 */
